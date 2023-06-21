// Richard Hill


#include "Spell_SlamAOE.h"

#include "GP3Team3/Player/PlayerCharacter.h"
#include "GP3Team3/Player/CustomComponents/Health/HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

ASpell_SlamAOE::ASpell_SlamAOE()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASpell_SlamAOE::BeginPlay()
{
	Super::BeginPlay();
	ActorsToIgnore.Add(OwnerActor);
	PlayerRef = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
}

void ASpell_SlamAOE::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASpell_SlamAOE::Activate()
{
	Super::Activate();

	// TODO: Activate the animation montage first,
	// TODO: when it reaches a certain point, then activate this spell
	AOESlam();
}

void ASpell_SlamAOE::AOESlam()
{
	TArray<FHitResult> HitArray;
	FVector Start = OwnerActor->GetActorLocation();
	FVector End = OwnerActor->GetActorLocation();
		
	const bool Hit = UKismetSystemLibrary::SphereTraceMulti(GetWorld(),
		Start,
		End,
		ThirdSwipeAOE * PlayerStats->AttackRangeMultiplier,
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

void ASpell_SlamAOE::CheckHit(bool Hit, TArray<FHitResult> HitArray)
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
					HealthComponent->TakeDamageInternal(Damage);
					DamagedActors.Add(HitActor);
				}
			}
		}
	}
}

