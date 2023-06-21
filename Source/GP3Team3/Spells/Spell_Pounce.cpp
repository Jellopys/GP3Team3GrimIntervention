// Fill out your copyright notice in the Description page of Project Settings.


#include "Spell_Pounce.h"

#include "GP3Team3/Player/PlayerCharacter.h"
#include "GP3Team3/Player/CustomComponents/Health/HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

ASpell_Pounce::ASpell_Pounce()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASpell_Pounce::BeginPlay()
{
	Super::BeginPlay();
	CachedChargeUpTime = ChargeUpTime;
	CachedChargeTime = ChargeTime;
	ChargeUpTime = 0;
	PlayerRef = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
}

void ASpell_Pounce::Tick(float DeltaTime)
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

	PounceForward(DeltaTime);
	
}

void ASpell_Pounce::Activate()
{
	Super::Activate();
	
	ChargeUpTime = CachedChargeUpTime;
	ChargeTime = CachedChargeTime;
	FakeLerp = CachedChargeTime;
	bIsAttacking = true;
	
	// When player is in range, charge up the attack and pounce forward when charge up is done
	// Rotate slowly toward the player during chargeUp
}

void ASpell_Pounce::ResetTimers()
{
	ChargeUpTime = CachedChargeUpTime;
	ChargeTime = CachedChargeTime;
	FakeLerp = CachedChargeTime;
	IgnoreActor = nullptr; // Clear the damaged actor
	bIsAttacking = false;
}

void ASpell_Pounce::PounceForward(float DeltaTime)
{
	if (ChargeTime > 0)
	{
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
			ResetTimers();
		}
	}
	else
	{
		ResetTimers();
	}
}

void ASpell_Pounce::RotateTowardPlayer(float DeltaTime)
{
	FRotator const CurrentRot = OwnerActor->GetActorRotation();
	// FRotator const TargetRot = UKismetMathLibrary::FindLookAtRotation(OwnerActor->GetActorLocation(), PlayerRef->GetActorLocation());
	FRotator const TargetRot = UKismetMathLibrary::FindLookAtRotation(OwnerActor->GetActorLocation(), PlayerRef->GetPlayerFuturePos(PlayerFuturePosDeltaFrames));
	FRotator const TargetRotXZ = FRotator(CurrentRot.Pitch, TargetRot.Yaw,TargetRot.Roll);
	
	OwnerActor->SetActorRotation(FMath::Lerp(CurrentRot, TargetRotXZ, ChargeUpTurnRate * DeltaTime)); // Rotate toward player
}

void ASpell_Pounce::SweepForward()
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

void ASpell_Pounce::CheckHit(bool Hit, TArray<FHitResult> HitArray)
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

