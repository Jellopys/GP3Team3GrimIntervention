// Richard Hill


#include "Spell_ScytheToss.h"

#include "GP3Team3/Player/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Projectiles/ForwardProjectile.h"

ASpell_ScytheToss::ASpell_ScytheToss()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASpell_ScytheToss::BeginPlay()
{
	Super::BeginPlay();
	CachedChargeUpTime = ChargeUpTime;
	CachedChargeTime = ChargeTime;
	ChargeUpTime = 0;
	PlayerRef = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
}

void ASpell_ScytheToss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bIsAttacking) return;

	if (ChargeUpTime > 0)
	{
		ChargeUpTime -= DeltaTime;
		RotateTowardPlayer(DeltaTime);
	}
	else
	{
		ChargeUpTime = CachedChargeUpTime;
		ChargeTime = CachedChargeTime;
		bIsAttacking = false;
	}
}

void ASpell_ScytheToss::Activate()
{
	Super::Activate();

	
	ChargeUpTime = CachedChargeUpTime;
	ChargeTime = CachedChargeTime;
	FakeLerp = CachedChargeTime;
	bIsAttacking = true;
	
	// When player is in range, charge up the attack and pounce forward.
	// Rotate slowly toward the player
	// Play the whole animation before continuing.
}

void ASpell_ScytheToss::RotateTowardPlayer(float DeltaTime)
{
	FRotator const CurrentRot = OwnerActor->GetActorRotation();
	FRotator const TargetRot = UKismetMathLibrary::FindLookAtRotation(OwnerActor->GetActorLocation(), PlayerRef->GetActorLocation());
	FRotator const TargetRotXZ = FRotator(CurrentRot.Pitch, TargetRot.Yaw,TargetRot.Roll);
	
	OwnerActor->SetActorRotation(FMath::Lerp(CurrentRot, TargetRotXZ, ChargeUpTurnRate * DeltaTime)); // Rotate toward player
}

void ASpell_ScytheToss::ReleaseProjectile()
{
	FVector SpawnLoc = OwnerActor->GetActorLocation() + OwnerActor->GetActorForwardVector() * ForwardSpawnPosLength;
	FRotator SpawnRot = OwnerActor->GetActorRotation();
	auto Arrow = GetWorld()->SpawnActor<AForwardProjectile>(Projectile, SpawnLoc, SpawnRot);
	if (Arrow)
	{
		Arrow->AssignParent(OwnerActor);
	}
}
