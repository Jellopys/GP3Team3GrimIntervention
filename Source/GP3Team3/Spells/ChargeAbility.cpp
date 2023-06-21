// Fill out your copyright notice in the Description page of Project Settings.


#include "ChargeAbility.h"

#include "GP3Team3/Player/PlayerCharacter.h"
#include "GP3Team3/Player/CustomComponents/Health/HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

AChargeAbility::AChargeAbility()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AChargeAbility::BeginPlay()
{
	Super::BeginPlay();
	CachedChargeUpTime = ChargeUpTime;
	CachedChargeTime = ChargeTime;
	ChargeUpTime = 0;
	PlayerRef = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
}

void AChargeAbility::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (OwnerActor == nullptr) return;

	if (!bIsAttacking) return;

	if (ChargeUpTime > 0)
	{
		ChargeUpTime -= DeltaTime;
		RotateTowardPlayer(DeltaTime);
		return;
	}
	
	ChargeForward(DeltaTime);
}

void AChargeAbility::Activate()
{
	Super::Activate();
	
	ChargeUpTime = CachedChargeUpTime;
	ChargeTime = CachedChargeTime;
	FakeLerp = CachedChargeTime;
	CachedChargeSpeed = ChargeSpeed;
	bIsAttacking = true;
	
	// When player is in range, charge up the attack and pounce forward.
	// Rotate slowly toward the player during chargeUp
	// Play the whole animation before continuing.
}

void AChargeAbility::ResetTimers()
{
	ChargeUpTime = CachedChargeUpTime;
	ChargeTime = CachedChargeTime;
	FakeLerp = CachedChargeTime;
	ChargeSpeed = CachedChargeSpeed;
	IgnoreActor = nullptr; // Clear the damaged actor
	bIsAttacking = false;
}

void AChargeAbility::RotateTowardPlayer(float DeltaTime)
{
	FRotator const CurrentRot = OwnerActor->GetActorRotation();
	// FRotator const TargetRot = UKismetMathLibrary::FindLookAtRotation(OwnerActor->GetActorLocation(), PlayerRef->GetActorLocation());
	FRotator const TargetRot = UKismetMathLibrary::FindLookAtRotation(OwnerActor->GetActorLocation(), PlayerRef->GetPlayerFuturePos(PlayerFuturePosDeltaFrames));
	FRotator const TargetRotXZ = FRotator(CurrentRot.Pitch, TargetRot.Yaw,TargetRot.Roll);
	
	OwnerActor->SetActorRotation(FMath::Lerp(CurrentRot, TargetRotXZ, ChargeUpTurnRate * DeltaTime)); // Rotate toward player
}

void AChargeAbility::ChargeForward(float DeltaTime)
{
	if (ChargeTime > 0)
	{
		if ((OwnerActor->GetActorLocation() - PlayerRef->GetActorLocation()).Length() <= StopDistance)
		{
			ChargeSpeed = SlowedChargeSpeed;
		}
		FHitResult HitResult;
		FVector const Forward = OwnerActor->GetActorForwardVector() * (ChargeSpeed * FakeLerp) * DeltaTime;
		OwnerActor->AddActorWorldOffset(Forward, true, &HitResult);
		FakeLerp -= DeltaTime;
		ChargeTime -= DeltaTime;

		if (HitResult.bBlockingHit)
		{
			AActor* HitActor = HitResult.GetActor();
			if (HitActor && HitActor == PlayerRef)
			{
				PlayerRef->GetHealthComponent()->TakeDamageInternal(Damage);
			}
			UE_LOG(LogTemp,Warning,TEXT("HIT"));
			ResetTimers();
		}
	}
	else
	{
		ResetTimers();
	}
}

void AChargeAbility::SweepForward()
{
	if (IgnoreActor != nullptr) return; // If player has been damaged, stop sweeping
	
	TArray<FHitResult> HitArray;
	FVector Start = OwnerActor->GetActorLocation();
	FVector End = OwnerActor->GetActorLocation() + OwnerActor->GetActorForwardVector() * ForwardSweepRange;
		
	const bool Hit = UKismetSystemLibrary::SphereTraceMulti(GetWorld(),
		Start,
		End,
		SphereRadius,
		UEngineTypes::ConvertToTraceType(ECC_WorldDynamic),
		false,
		ActorsToIgnore,
		EDrawDebugTrace::ForDuration,
		HitArray,
		true,
		FLinearColor::Red,
		FLinearColor::Blue,
		DebugDrawTime);

	CheckHit(Hit, HitArray);
}

void AChargeAbility::CheckHit(bool Hit, TArray<FHitResult> HitArray)
{
	if (Hit && HitArray.Num()!=0)
	{
		for (const FHitResult HitResult : HitArray)
		{
			AActor* HitActor = HitResult.GetActor();
			if (!HitActor) return;
			if (HitActor == OwnerActor) return;
			if (HitActor != PlayerRef) return;
			
			if (UHealthComponent* HealthComponent = HitActor->FindComponentByClass<UHealthComponent>())
			{
				if (HealthComponent->GetIsImmune()) return;
				
				HealthComponent->TakeDamageInternal(Damage);
				IgnoreActor = HitActor;
			}
		}
	}
}

