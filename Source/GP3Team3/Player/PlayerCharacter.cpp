// Richard Hill

#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/SkeletalMeshComponent.h"
#include "CustomComponents/Movement/PlayerMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/GameViewportClient.h"
#include "GrimPlayerController.h"
#include "CustomComponents/Health/HealthComponent.h"
#include "GP3Team3/GameEssentials/GrimGameInstance.h"
#include "GP3Team3/GameEssentials/GrimGameMode.h"
#include "GP3Team3/Spells/BaseSpell.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Components/StaticMeshComponent.h"
#include "GP3Team3/Spells/Projectiles/ScytheProjectile.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	RootComponent = Capsule;
	Capsule->SetCollisionProfileName("BlockAllDynamic");

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Character Mesh"));
	Mesh->SetupAttachment(Capsule);

	FirePos = CreateDefaultSubobject<USceneComponent>(TEXT("Fire Position"));
	FirePos->SetupAttachment(Capsule);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	MovementComponent = CreateDefaultSubobject<UPlayerMovementComponent>(TEXT("Movement Component"));
	MovementComponent->SetUpdatedComponent(Capsule);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));

	AuraComponent = CreateDefaultSubobject<UAuraComponent>(TEXT("Aura Component"));

	ScytheMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Scythe Mesh"));
	ScytheMesh->SetupAttachment(Mesh);
}

void APlayerCharacter::ForceCancelAnimation()
{
	UAnimInstance* const AnimInstance = (Mesh)? Mesh->GetAnimInstance() : nullptr; 
	if ( AnimInstance )
	{
		AnimInstance->StopAllMontages(0.01f);
	}
}

void APlayerCharacter::SetCanMove(bool CanMove)
{
	if (HealthComponent->GetIsDead())
	{
		bIsAllowedToMove = false;
		return;
	}
	bIsAllowedToMove = CanMove;
}

void APlayerCharacter::SpawnScytheProjectile()
{
	ScytheSpawned->SetActiveStatus(true);
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	ScytheMesh->AttachToComponent(Mesh, FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), TEXT("wrist_r"));

	CurrentStamina = MaxStamina;

	if (ScytheSpawned = GetWorld()->SpawnActor<AScytheProjectile>(ScytheProjectile, FVector::ZeroVector, FRotator::ZeroRotator))
	{
		ScytheSpawned->AssignParent(this);
		ScytheSpawned->SetActiveStatus(false);
	}

	CameraRoll = SpringArm->GetRelativeRotation().Roll;
	CameraPitch = SpringArm->GetRelativeRotation().Pitch;
	CameraTargetRotation = FRotator(CameraRoll, 45, CameraPitch);
	RotateCameraRight();
	
	GrimGameMode = Cast<AGrimGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	GrimGameInstance = Cast<UGrimGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	
	MovementData = MovementComponent->GetMovementData();
	
	PlayerController = Cast<AGrimPlayerController>(GetWorld()->GetFirstPlayerController());
	
	if(MovementData != nullptr)
	{
		// Speed = MovementData->MoveSpeed;
		Gravity = MovementData->Gravity;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No movement Data-Asset found"));
	}

	CachedDashDuration = DashDuration;
	
	Camera = Cast<UCameraComponent>(GetComponentByClass(UCameraComponent::StaticClass()));
	SpringArm = Cast<USpringArmComponent>(GetComponentByClass(USpringArmComponent::StaticClass()));
	MouseOrbVisual = GetWorld()->SpawnActor<AActor>(MouseOrb);
	
	if (!bIsOrbActive)
		MouseOrbVisual->SetActorHiddenInGame(true);

	////// TESTING
	if (Spell != nullptr)
	{
		CurrentSpell = GetWorld()->SpawnActor<ABaseSpell>(Spell);
		CurrentSpell->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
		CurrentSpell->AssignOwner(this);
	}
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Mouse & Camera
	UpdateMousePosition(DeltaTime);
	RotateCamera(DeltaTime);

	// Movement & Input
	RotatePlayer(DeltaTime);
	HandleInput(DeltaTime);
	MovePlayer(DeltaTime);

	// Stamina
	HandleStamina(DeltaTime);

	// Dash
	CheckDash();
	DashDuration -= DeltaTime;
}

void APlayerCharacter::HandleInput(float DeltaTime)
{
	if (!InputVector.IsNearlyZero())
	{
		FVector CameraForward = Camera->GetForwardVector();
		FVector Forward = FVector(CameraForward.X, CameraForward.Y, 0);
		FVector ForwardMovement = Forward * InputVector.X;
		FVector CameraRight = Camera->GetRightVector();
		FVector Right = FVector(CameraRight.X,CameraRight.Y, 0);
		FVector RightMovement = Right * InputVector.Y;
		
		Velocity = (ForwardMovement + RightMovement).GetSafeNormal() * GrimGameInstance->PlayerStats->MovementSpeed * DeltaTime * MovementData->Acceleration;
	}
	else
	{
		Velocity = FMath::Lerp(Velocity, FVector::ZeroVector, DeltaTime * Deceleration);
	}
}

void APlayerCharacter::PerformAttack()
{
	if (bIsCasting) return;
	
	if (CurrentSpell && !bIsKicking)
	{
		CurrentSpell->Activate();
		OnAttack();
	}
}

void APlayerCharacter::ReleasePrimary()
{
	if (CurrentSpell != nullptr)
	{
		CurrentSpell->Release();
		OnReleasePrimary();
	}
}

void APlayerCharacter::RotateTowardMouse(const bool Enabled)
{
	// if (Enabled == PrevEnabled) return;
	bIsAttacking = Enabled;
	if (Enabled)
	{
		SetActorRotation(UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), MouseOrbVisual->GetActorLocation()));
	}
	PrevEnabled = Enabled;
}

float APlayerCharacter::PlayAnimationMontage(UAnimMontage* Montage, float InPlayRate, FName StartSectionName)
{
	UAnimInstance * AnimInstance = (Mesh)? Mesh->GetAnimInstance() : nullptr; 
	if ( Montage && AnimInstance )
	{
		float Duration = AnimInstance->Montage_Play(Montage, InPlayRate);
		
		if (Duration > 0.f)
		{
			// Start at a given Section.
			if( StartSectionName != NAME_None )
			{
				AnimInstance->Montage_JumpToSection(StartSectionName, Montage);
				int const MontageSectionID = Montage->GetSectionIndex(StartSectionName);
				Duration = Montage->GetSectionLength(MontageSectionID);
			}
			return Duration;
		}
	}
	return 0;
}

void APlayerCharacter::SetIsAttacking(bool InBool)
{
	bIsAttacking = InBool;
}

void APlayerCharacter::SetIsCasting(bool IsCasting)
{
	bIsCasting = IsCasting;
}

void APlayerCharacter::MovePlayer(float DeltaTime)
{
	if (HealthComponent->GetIsDead()) return;
	
	FMovementStatics FrameMovement = MovementComponent->CreateFrameMovement();
	FrameMovement.AddGravity(Gravity * DeltaTime);
	
	if (!InputVector.IsNearlyZero())
	{
		if (Dashing) // Player is now dashing
		{
			float DashDelta = DashDuration * GrimGameInstance->PlayerStats->DashPower; 
			DashDelta = FMath::Clamp(DashDelta, 1, 999999);
			FrameMovement.AddDelta(Velocity * DashDelta);
		}
		else // Player Movement speed is now normal
		{
			FrameMovement.AddDelta(Velocity);
		}
		if (bIsAllowedToMove) // Move player unless stunned
		{
			MovementComponent->Move(FrameMovement);
		}
	}
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent)
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);
	PlayerInputComponent->BindAction("Dash", IE_Pressed, this, &APlayerCharacter::Dash);
	PlayerInputComponent->BindAction("Kick", IE_Pressed, this, &APlayerCharacter::Kick);
	PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &APlayerCharacter::PerformAttack);
	PlayerInputComponent->BindAction("PrimaryAttack", IE_Released, this, &APlayerCharacter::ReleasePrimary);
	PlayerInputComponent->BindAction("RotateCamera", IE_Pressed, this, &APlayerCharacter::EnableCameraRotation);
	PlayerInputComponent->BindAction("RotateCamera", IE_Released, this, &APlayerCharacter::ReleaseCamera);
	PlayerInputComponent->BindAction("RotateCameraLeft", IE_Pressed, this, &APlayerCharacter::RotateCameraLeft);
	PlayerInputComponent->BindAction("RotateCameraRight", IE_Pressed, this, &APlayerCharacter::RotateCameraRight);
	PlayerInputComponent->BindAction("CastScythe", IE_Pressed, this, &APlayerCharacter::CastScythe);
}

bool APlayerCharacter::CheckStaminaCost(float StaminaCost)
{
	if (CurrentStamina < StaminaCost) // If you have less stamina than the stamina cost
	{
		return false;
	}
	return true;
}

void APlayerCharacter::CastScythe()
{
	if (bIsAttacking) return; // Cannot cast if you're attacking
	if (bIsKicking) return; // Cannot cast if you're kicking
	if (bIsCasting) return; // Cannot cast if scythe is out already
	if (Dashing) return; // Cannot cast if Dashing

	if (!CheckStaminaCost(GrimGameInstance->PlayerStats->ScytheTossStaminaCost)) return;
	
	UseStamina(GrimGameInstance->PlayerStats->ScytheTossStaminaCost, true);
	
	SetActorRotation(UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), MouseOrbVisual->GetActorLocation()));
	float const AnimDuration = PlayAnimationMontage(ScytheTossMontage, 1, NAME_None);

	SetIsCasting(true);
	bIsAllowedToMove = false;
	bIsAttacking = true;

	OnScytheCast();

	// FTimerHandle Timer;
	// GetWorld()->GetTimerManager().SetTimer(Timer, this, &APlayerCharacter::ScytheReturn,AnimDuration * ScytheTossAnimFreeMove);
}

void APlayerCharacter::ScytheReturn()
{
	bIsAllowedToMove = true;
}

void APlayerCharacter::RotateCameraRight()
{
	float const CurrentYawRot = CameraTargetRotation.Yaw;
	CameraTargetRotation = FRotator(CameraPitch, CurrentYawRot + 90, CameraRoll);
}

void APlayerCharacter::RotateCameraLeft()
{
	float const CurrentYawRot = CameraTargetRotation.Yaw;
	CameraTargetRotation = FRotator(CameraPitch, CurrentYawRot - 90, CameraRoll);
}

void APlayerCharacter::Kick()
{
	if (bIsAttacking || bIsKicking) return; // Cannot kick if you're attacking

	SetActorRotation(UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), MouseOrbVisual->GetActorLocation()));
	float const AnimDuration = PlayAnimationMontage(KickMontage, 1, NAME_None);
	
	bIsKicking = true;
	bIsAllowedToMove = false;
	OnKick();

	FTimerHandle Timer;
	GetWorld()->GetTimerManager().SetTimer(Timer, this, &APlayerCharacter::KickEnd,AnimDuration * 0.8f);
	
}

void APlayerCharacter::KickEnd()
{
	bIsKicking = false;
	bIsAllowedToMove = true;
}

void APlayerCharacter::UseStamina(float StaminaCost, bool ActivateRegainCooldown)
{
	CurrentStamina -= StaminaCost;
	if (ActivateRegainCooldown)
	{
		CanRechargeStamina = false;
		GetWorld()->GetTimerManager().ClearTimer(StaminaTimerDelegate); // This is to reset the timer
        	GetWorld()->GetTimerManager().SetTimer(StaminaTimerDelegate, this, &APlayerCharacter::RegainStaminaRecharge,
        		GrimGameInstance->PlayerStats->StaminaRegainTime, false);
	}
}

void APlayerCharacter::RegainStaminaRecharge()
{
	CanRechargeStamina = true;
}

void APlayerCharacter::HandleStamina(float DeltaTime)
{
	if (!CanRechargeStamina)
		return;
	CurrentStamina = FMath::Clamp(CurrentStamina += DeltaTime * GrimGameInstance->PlayerStats->StaminaGainMultiplier,
		0, GrimGameInstance->PlayerStats->MaxStamina);
}

void APlayerCharacter::RotateCamera(float DeltaTime)
{
	// if (!bRotatingCamera) return;
	//
	// FVector2D MousePositionDelta = FVector2D(0, 0);
	// PlayerController->GetInputMouseDelta(MousePositionDelta.X, MousePositionDelta.Y);
	//
	// // /// VERTICAL CAMERA MOVEMENT
	// // float pitch = mousePositionDelta.Y * CameraRotationSpeed;
	// // if (SpringArm->GetRelativeRotation().Pitch < -65 && pitch < 0 ||
	// // 	SpringArm->GetRelativeRotation().Pitch > -30 && pitch > 0)
	// // {
	// // 	pitch = 0;
	// // }
	// // FRotator targetRotation = FRotator(pitch, mousePositionDelta.X * CameraRotationSpeed, 0);
	//
	// FRotator TargetRotation = FRotator(0, MousePositionDelta.X * CameraRotationSpeed, 0);
	// FRotator Rotation = FMath::RInterpConstantTo(FRotator::ZeroRotator, TargetRotation, DeltaTime, 0);
	//
	// SpringArm->AddRelativeRotation(Rotation);

	// FRotator Rotation = FMath::RInterpConstantTo(FRotator::ZeroRotator, CameraTargetRotation, DeltaTime, 0);
	FRotator Rot = FMath::Lerp(SpringArm->GetRelativeRotation(), CameraTargetRotation, DeltaTime * CameraRotationSpeed);
	// SpringArm->AddRelativeRotation(Rot);
	SpringArm->SetRelativeRotation(Rot);
}

void APlayerCharacter::EnableCameraRotation()
{
	bRotatingCamera = true;
}

void APlayerCharacter::ReleaseCamera()
{
	bRotatingCamera = false;
}

void APlayerCharacter::MoveForward(float Val)
{
	if (!bIsAllowedToMove)
		return;
	InputVector.X = Val;
}

void APlayerCharacter::MoveRight(float Val)
{
	if (!bIsAllowedToMove)
		return;
	InputVector.Y = Val;
}

void APlayerCharacter::UpdateMousePosition(float DeltaTime)
{
	// if (bRotatingCamera) return;
	
	MousePosition = FVector2D(0, 0);
	PlayerController->GetMousePosition(MousePosition.X, MousePosition.Y);
	FVector CameraLocation, TargetDirection;
	PlayerController->DeprojectScreenPositionToWorld(
		MousePosition.X, MousePosition.Y, CameraLocation, TargetDirection);
	TargetDirection *= SpringArm->TargetArmLength; 
	FVector TargetPos = TargetDirection += CameraLocation; 
	FVector Intersection = FMath::LinePlaneIntersection(
		CameraLocation, TargetPos, GetActorLocation(), FVector(0, 0, 1));

	FVector targetLocation = FMath::Lerp(MouseOrbVisual->GetActorLocation(), Intersection, MouseOrbLerpSpeed * DeltaTime);
	// Set the Mouse orbs position
	MouseOrbVisual->SetActorRelativeLocation(targetLocation); 

	// Rotate the mouse orb towards the player
	// MouseOrbVisual->SetActorRotation(UKismetMathLibrary::FindLookAtRotation(Intersection, GetActorLocation()));
	FRotator targetRotation = UKismetMathLibrary::FindLookAtRotation(Intersection, MouseOrbVisual->GetActorLocation());

	MouseOrbVisual->SetActorRotation(FMath::Lerp(MouseOrbVisual->GetActorRotation(), targetRotation, MouseOrbLerpSpeed * DeltaTime)); 
	
}

void APlayerCharacter::RotatePlayer(float DeltaTime)
{
	CurrentRot = GetActorRotation();

	if (bIsAttacking || bIsKicking) return; // When attacking, we dont want to constantly update the rotation
	
	// if (bIsAttacking)
	// {
	// 	SetActorRotation(UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), MouseOrbVisual->GetActorLocation()));
	// 	return;
	// }
	
	if (!InputVector.IsNearlyZero())
	{
		if (Velocity != PrevVelocity)
		{
			TurnDelta = 0;
		}
		if (CurrentRot != Velocity.ToOrientationRotator())
		{
			TurnDelta += DeltaTime * TurnRate;
			SetActorRotation(FQuat::Slerp(CurrentRot.Quaternion(), Velocity.ToOrientationQuat(), TurnDelta / TurnSpeed)); // Rotate player
			PrevVelocity = Velocity;
		}
	}
}

void APlayerCharacter::CheckDash()
{
	if (DashDuration > 0)
	{
		Dashing = true;
	}	
	else
	{
		Dashing = false;
	}
}

void APlayerCharacter::Dash()
{
	if (!CheckStaminaCost(GrimGameInstance->PlayerStats->DashStaminaCost))
		return;
	if (DashDuration + GrimGameInstance->PlayerStats->DashCooldown < 0 &&
		(InputVector.X != 0 || InputVector.Y != 0) && bDashLegal)
	{
		
		bIsKicking = false;
		bIsAllowedToMove = true;
		ForceCancelAnimation();
		RotateTowardMouse(false);
		// ScytheMesh->SetCollisionResponseToAllChannels(ECR_Ignore);
		
		float const AnimDuration = PlayAnimationMontage(DashMontage, 1, NAME_None);
		
		OnDash(GetActorLocation(), GetActorRotation());
		OnDashC();
		DashDuration = GrimGameInstance->PlayerStats->DashDuration;
		UseStamina(GrimGameInstance->PlayerStats->DashStaminaCost, true);
		FTimerHandle Timer;
		FTimerHandle Timer2;
		GetWorld()->GetTimerManager().SetTimer(Timer, this, &APlayerCharacter::OnDashEnd, DashDuration, false);
		GetWorld()->GetTimerManager().SetTimer(Timer2, this, &APlayerCharacter::OnDashEndC, DashDuration, false);
	}
}

void APlayerCharacter::OnDashC()
{
	Capsule->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECR_Overlap);
	HealthComponent->DashImmunity(true);
}

void APlayerCharacter::OnDashEndC()
{
	Capsule->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECR_Block);
	HealthComponent->DashImmunity(false);
}


UCameraComponent* APlayerCharacter::GetCamera()
{
	return Camera;
}

AActor* APlayerCharacter::GetOrb()
{
	return MouseOrbVisual;
}

FVector APlayerCharacter::GetPlayerFuturePos(float InDeltaFrames)
{
	return GetActorLocation() + (Velocity * InDeltaFrames);
}

UHealthComponent* APlayerCharacter::GetHealthComponent()
{
	return HealthComponent;
}
