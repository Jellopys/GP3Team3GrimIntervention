// Richard Hill

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GP3Team3/WFCTestCpp/TileBase.h"
#include "BaseEnemy.generated.h"

class AGrimAIController;
class UCapsuleComponent;
class UHealthComponent;
class ABaseSpell;
class UBehaviorTree;

// UCLASS(HideCategories=(Input, Movement, Collision, Rendering, HLOD, WorldPartition, DataLayers, Tags, Replication, Cooking))
UCLASS()
class ABaseEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	ABaseEnemy();
	
	/////// Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Health)
	UHealthComponent* HealthComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AI)
	UBehaviorTree* BehaviorTree;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spells)
	TSubclassOf<ABaseSpell> Spell;
	UPROPERTY()
	ABaseSpell* CurrentSpell;
	UPROPERTY()
	ATileBase* OwningTile;

	UPROPERTY(VisibleAnywhere)
	float AttackTime = 2;

	float GetAttackTime();
	
	UFUNCTION()
	void WhenKilled(AActor* DestroyedActor);

	UFUNCTION(BlueprintCallable, Category = Combat)
	void PerformAttack();

	UFUNCTION(BlueprintCallable)
	float PlayAnimationMontage(UAnimMontage* Montage, float InPlayRate, FName StartSectionName);
	UFUNCTION(BlueprintImplementableEvent)
	float PlayAnimationMontageBP();
	UFUNCTION(BlueprintCallable)
	void RotateTowardPlayer();
	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void Destroyed() override;

	UPROPERTY()
	AGrimAIController* AIController;
};
