// Richard Hill


#include "ComboSwipe.h"

#include "GP3Team3/Player/PlayerCharacter.h"
#include "GP3Team3/Player/CustomComponents/Health/HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Animation/AnimMontage.h"

AComboSwipe::AComboSwipe()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AComboSwipe::JumpForward(float DeltaTime)
{
	FVector const ForwardVector = PlayerRef->GetActorForwardVector() * JumpSpeed * DeltaTime;
	
	// SetActorLocation(FMath::Lerp(GetActorLocation(), TargetLocation, TravelDelta / TravelDistance));
	if (JumpDelta > 0)
	{
		JumpDelta -= DeltaTime;
		FHitResult Hit;
		PlayerRef->AddActorWorldOffset(ForwardVector, true, &Hit);
		if (Hit.bBlockingHit)
		{
			JumpDelta = 0;
		}
	}
}

void AComboSwipe::BeginPlay()
{
	Super::BeginPlay();
	ActorsToIgnore.Add(OwnerActor);
	PlayerRef = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
}

void AComboSwipe::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CheckCooldown(DeltaTime);
	HandleChainComboTime(DeltaTime);
	JumpForward(DeltaTime);
}

void AComboSwipe::Activate()
{
	Super::Activate();
	
	// handle input, if CurrentCombo is 0. Attack First Hit.
	// If currentcombo is > 0, check InputGracePeriod
	// if you do a input before a inputgraceperiod, the input is ignored
	// The input grace period is the last half of the total attack time.
	// If you successfully chained the attack, ChainAttack
	// During attacks, you are stopped in place.

	if (bIsOnCooldown) return;
	if (!CanChain()) return;

	// Stop player movement
	HandlePlayerMovement(true);

	JumpDelta = JumpTime;
	
	switch (CurrentCombo)
	{
	case 0:
		FirstHit();
		break;
	case 1:
		SecondHit();
		break;
	case 2:
		ThirdHit();
		break;
	default:
		FirstHit();
		break;
	}

	testbool = true;
	PlayerRef->UseStamina(StaminaCost, bUseStaminaRegainCd);
	CurrentCombo++;
	bIsAttacking = true;
	PlayerRef->SetIsAttacking(true);
	ChainTimer = MontageDuration;
}

void AComboSwipe::FirstHit()
{
	if (ComboMontage)
	{
		float Dur = PlayerRef->PlayAnimationMontage(ComboMontage, PlayerStats->AttackSpeed, TEXT("FirstCombo"));
		MontageDuration = Dur / PlayerStats->AttackSpeed;
		UE_LOG(LogTemp,Warning,TEXT("Attackspeed is : %f"), PlayerStats->AttackSpeed);
	}
}

void AComboSwipe::SecondHit()
{
	if (ComboMontage)
	{
		float Dur = PlayerRef->PlayAnimationMontage(ComboMontage, PlayerStats->AttackSpeed, TEXT("SecondCombo"));
		MontageDuration = Dur / PlayerStats->AttackSpeed;
	}
}

void AComboSwipe::ThirdHit()
{
	if (ComboMontage)
	{
		float Dur = PlayerRef->PlayAnimationMontage(ComboMontage, PlayerStats->AttackSpeed, TEXT("ThirdCombo"));
		MontageDuration = Dur / PlayerStats->AttackSpeed;
	}

	LastComboCooldownTimer = MontageDuration;
	bIsOnCooldown = true;
	CurrentCombo = 0;
}

void AComboSwipe::HandleChainComboTime(float DeltaTime)
{
	if (!bIsAttacking) return;

	if (ChainTimer < MontageDuration * CanMoveTimer && testbool)
	{
		HandlePlayerMovement(false);
		testbool = false;
	}
	
	if (ChainTimer > 0)
	{
		ChainTimer -= DeltaTime;
	}
	else
	{
		// HandlePlayerMovement(false);
		CurrentCombo = 0;
		PlayerRef->SetIsAttacking(false);
		bIsAttacking = false;
	}
}

void AComboSwipe::CheckHit(bool Hit, TArray<FHitResult> HitArray)
{
	PlaySound();
	if (Hit && HitArray.Num()!=0)
	{
		TArray<AActor*> DamagedActors;
		for (const FHitResult HitResult : HitArray)
		{
			AActor* HitActor = HitResult.GetActor();
			if (DamagedActors.Contains(HitActor)) continue; // Do not damage actor that has already been damaged.
			
			if (HitActor != OwnerActor && HitActor)
			{
				if (UHealthComponent* HealthComponent = HitActor->FindComponentByClass<UHealthComponent>())
				{
					DealDamage(HealthComponent);
					DamagedActors.Add(HitActor);
				}
			}
		}
	}
}


void AComboSwipe::HandlePlayerMovement(bool StopMovement)
{
	if (StopMovement)
	{
		// Stop Movement
		PlayerRef->bIsAllowedToMove = false;
		PlayerRef->RotateTowardMouse(StopMovement);
	}
	else
	{
		// Release Movement
		PlayerRef->bIsAllowedToMove = true;
		PlayerRef->RotateTowardMouse(StopMovement);
	}	
}

bool AComboSwipe::CanChain()
{
	if (CurrentCombo == 0) return true;
	
	if (ChainTimer > 0 && ChainTimer < MontageDuration * InputGracePeriod)
	{
		return true;
	}
	return false;
}

void AComboSwipe::CheckCooldown(float DeltaTime)
{
	if (!bIsOnCooldown) return;

	if (LastComboCooldownTimer > 0)
	{
		LastComboCooldownTimer -= DeltaTime;
	}
	else
	{
		bIsOnCooldown = false;
	}
}

void AComboSwipe::DealDamage(UHealthComponent* HealthComponent)
{
	if (CurrentCombo == 0)
		HealthComponent->TakeDamageInternal(PlayerStats->FirstComboDamage * PlayerStats->BaseDamageMultiplier);
	else if (CurrentCombo == 1)
		HealthComponent->TakeDamageInternal(PlayerStats->SecondComboDamage * PlayerStats->BaseDamageMultiplier);
	else
		HealthComponent->TakeDamageInternal(PlayerStats->ThirdComboDamage * PlayerStats->BaseDamageMultiplier);
}

