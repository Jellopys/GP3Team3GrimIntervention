#include "AuraComponent.h"

#include "GP3Team3/Enemy/EnemySpawner.h"
#include "GP3Team3/GameEssentials/GrimGameMode.h"
#include "GP3Team3/Player/CustomComponents/Health/HealthComponent.h"

UAuraComponent::UAuraComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UAuraComponent::OnAuraUnlocked()
{
	OnAuraGet.Broadcast();
}

void UAuraComponent::BeginPlay()
{
	Super::BeginPlay();

	Owner = GetOwner();

	InnerTimer = AuraIntervalTimer;

	TArray<UActorComponent*> AllAuraBoxes = Owner->GetComponentsByTag(UStaticMeshComponent::StaticClass(), FName("AuraBox"));
	AuraHitbox = Cast<UStaticMeshComponent>(AllAuraBoxes[0]);
	
	AuraHitbox->OnComponentBeginOverlap.AddDynamic(this, &UAuraComponent::OnComponentBeginOverlap);
	AuraHitbox->OnComponentEndOverlap.AddDynamic(this, &UAuraComponent::OnComponentEndOverlap);
}

void UAuraComponent::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor->GetClass()->IsChildOf(ABaseEnemy::StaticClass()))
	{
		ABaseEnemy* TempEnemy = Cast<ABaseEnemy>(OtherActor);
		RelevantEnemies.Add(TempEnemy);
	}
}

void UAuraComponent::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(OtherActor->GetClass()->IsChildOf(ABaseEnemy::StaticClass()))
	{
		ABaseEnemy* TempEnemy = Cast<ABaseEnemy>(OtherActor);
		EnemiesToRemove.Add(TempEnemy);
	}
}

void UAuraComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(!bHasAura)
	{
		return;
	}
	
	if(InnerTimer <= 0)
	{
		AGrimGameMode* GameModeRef = Cast<AGrimGameMode>(GetWorld()->GetAuthGameMode());
		
		for (auto Index {0}; Index <= RelevantEnemies.Num()-1; Index++)
		{
			RelevantEnemies[Index]->HealthComponent->TakeDamageInternal(BaseDamage + GameModeRef->TileTempAuraDamage);
			OnEnemyDamaged.Broadcast();
		}

		InnerTimer = AuraIntervalTimer;
	}

	for (auto Index {0}; Index <= EnemiesToRemove.Num()-1; Index++)
	{
		RelevantEnemies.Remove(EnemiesToRemove[Index]);
	}

	EnemiesToRemove.Empty();

	InnerTimer -= DeltaTime;
}

