// Richard Hill


#include "MeleeSwipeAbility.h"

#include "GP3Team3/Player/CustomComponents/Health/HealthComponent.h"
#include "Kismet/KismetSystemLibrary.h"

AMeleeSwipeAbility::AMeleeSwipeAbility()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMeleeSwipeAbility::BeginPlay()
{
	Super::BeginPlay();
	CachedChainTime = MaxChainTime;
}

void AMeleeSwipeAbility::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	HandleChainComboTime();
}

void AMeleeSwipeAbility::Activate()
{
	Super::Activate();
	
	switch (CurrentCombo)
	{
		case 0:
			FirstHit();
		case 1:
			SecondHit();
		case 2:
			ThirdHit();
		default:
			FirstHit();
	}
	HandleChainComboTime();
}

void AMeleeSwipeAbility::FirstHit()
{
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(OwnerActor);
	TArray<FHitResult> HitArray;
	FVector Start = OwnerActor->GetActorLocation();
	FVector End = Start + OwnerActor->GetActorForwardVector() * AttackRange;
		
	const bool Hit = UKismetSystemLibrary::SphereTraceMulti(GetWorld(),
		Start,
		End,
		SwipeAOE,
		UEngineTypes::ConvertToTraceType(ECC_WorldDynamic),
		false,
		ActorsToIgnore,
		EDrawDebugTrace::ForDuration,
		HitArray,
		true,
		FLinearColor::Red,
		FLinearColor::Blue,
		3.0f);

	CheckHit(Hit, HitArray);
}

void AMeleeSwipeAbility::SecondHit()
{
	
}

void AMeleeSwipeAbility::ThirdHit()
{
	
}

void AMeleeSwipeAbility::HandleChainComboTime()
{
	
}

void AMeleeSwipeAbility::CheckHit(bool Hit, TArray<FHitResult> HitArray)
{
	if (Hit && HitArray.Num()!=0)
	{
		for (const FHitResult HitResult : HitArray)
		{
			AActor* HitActor = HitResult.GetActor();
			if (HitActor != OwnerActor && HitActor)
			{
				if (UHealthComponent* HealthComponent = HitActor->FindComponentByClass<UHealthComponent>())
				{
					HealthComponent->TakeDamageInternal(1);
				}
			}
		}
	}
}

