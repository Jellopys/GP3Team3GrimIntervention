// Richard Hill


#include "BaseEnemy.h"

#include "GrimAIController.h"
#include "GP3Team3/Spells/BaseSpell.h"
#include "GP3Team3/Player/CustomComponents/Health/HealthComponent.h"


ABaseEnemy::ABaseEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));
	
}


float ABaseEnemy::GetAttackTime()
{
	return AttackTime;
}

void ABaseEnemy::WhenKilled(AActor* DestroyedActor)
{
	if(OwningTile)
	{
		OwningTile->RegisterEnemyKill();
	}
}

void ABaseEnemy::PerformAttack()
{
	if (CurrentSpell != nullptr)
	{
		CurrentSpell->Activate();
	}
}

void ABaseEnemy::RotateTowardPlayer()
{
}

void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();

	this->OnDestroyed.AddDynamic(this, &ABaseEnemy::WhenKilled);

	AIController = Cast<AGrimAIController>(GetController());
	if (AIController)
	{
		AIController->SetBehaviorTree(BehaviorTree);
	}
	
	if (Spell != nullptr)
	{
		CurrentSpell = GetWorld()->SpawnActor<ABaseSpell>(Spell);
		CurrentSpell->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
		CurrentSpell->AssignOwner(this);
	}
}

void ABaseEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

float ABaseEnemy::PlayAnimationMontage(UAnimMontage* Montage, float InPlayRate, FName StartSectionName)
{
	USkeletalMeshComponent* SkeletalMesh = GetMesh();
	UAnimInstance* AnimInstance = (SkeletalMesh)? SkeletalMesh->GetAnimInstance() : nullptr;
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

void ABaseEnemy::Destroyed()
{
	Super::Destroyed();

	TArray<AActor*> AttachedActors;
	GetAttachedActors(AttachedActors);

	if (AttachedActors.Num() > 0)
	{
		for (AActor* AttachedActor : AttachedActors)
		{
			AttachedActor->Destroy();
		}
	}
}

