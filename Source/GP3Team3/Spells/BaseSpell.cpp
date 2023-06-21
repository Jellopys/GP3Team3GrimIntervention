// Richard Hill


#include "BaseSpell.h"

#include "GP3Team3/GameEssentials/GrimGameInstance.h"
#include "GP3Team3/Player/PlayerStats.h"
#include "Kismet/GameplayStatics.h"

ABaseSpell::ABaseSpell()
{
	PrimaryActorTick.bCanEverTick = true;
	CooldownTimer = Cooldown;
}

void ABaseSpell::BeginPlay()
{
	Super::BeginPlay();
	
	GrimGameInstance = Cast<UGrimGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	PlayerStats = GrimGameInstance->PlayerStats;
}

void ABaseSpell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (CooldownTimer > 0)
	{
		CooldownTimer -= DeltaTime;
	}
}

void ABaseSpell::Activate()
{
	if (Cooldown > 0)
	{
		return;
	}
	
	CooldownTimer = Cooldown;
}

void ABaseSpell::Release()
{
	
}

void ABaseSpell::AssignOwner(AActor* OwnerAct)
{
	OwnerActor = OwnerAct;
	AttachToActor(OwnerActor, FAttachmentTransformRules::KeepRelativeTransform);
}

