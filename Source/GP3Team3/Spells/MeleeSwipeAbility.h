// Richard Hill

#pragma once

#include "BaseSpell.h"
#include "MeleeSwipeAbility.generated.h"

UCLASS()
class AMeleeSwipeAbility : public ABaseSpell
{
	GENERATED_BODY()

public:
	AMeleeSwipeAbility();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SwipeAOE = 300;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AttackRange = 100;

	UPROPERTY()
	int CurrentCombo = 0;

	UPROPERTY()
	float MaxChainTime = 1;
	float CachedChainTime;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void Activate() override;
	void FirstHit();
	void SecondHit();
	void ThirdHit();
	void HandleChainComboTime();
	void CheckHit(bool Hit, TArray<FHitResult> HitArray);	
};
