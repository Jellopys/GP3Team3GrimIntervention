// Richard Hill

#pragma once

#include "BaseSpell.h"
#include "Spell_SlamAOE.generated.h"

class UHealthComponent;
class APlayerCharacter;

UCLASS()
class ASpell_SlamAOE : public ABaseSpell
{
	GENERATED_BODY()

public:
	ASpell_SlamAOE();

	// First Strike
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FirstSwipeAOE = 60;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FirstAttackRange = 100;

	// Second Strike
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SecondSwipeAOE = 70;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SecondAttackRange = 150;

	// Third Strike
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ThirdSwipeAOE = 300;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DebugDrawTime = 0.0f;

	UFUNCTION(BlueprintImplementableEvent)
	void PlaySound();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float Damage = 5;
	
	bool bIsAttacking = false;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void Activate() override;

	UPROPERTY()
	TArray<AActor*> ActorsToIgnore;
	UPROPERTY()
	APlayerCharacter* PlayerRef;

	// Functions
	void AOESlam();
	void CheckHit(bool Hit, TArray<FHitResult> HitArray);
};
