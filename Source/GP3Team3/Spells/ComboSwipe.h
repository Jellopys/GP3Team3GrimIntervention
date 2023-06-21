// Richard Hill

#pragma once

#include "BaseSpell.h"
#include "ComboSwipe.generated.h"

class UHealthComponent;
class APlayerCharacter;

UCLASS()
class AComboSwipe : public ABaseSpell
{
	GENERATED_BODY()

public:
	AComboSwipe();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* ComboMontage;

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
	
	/** It's a percentage of the remaining time where your input will successfully chain an attack.
	 * 0.1 is the last 10% of the total Attack Time (Chain Time). 1 is ANYTIME after the previous attack.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ClampMin=0.3, ClampMax=1.0f))
	float InputGracePeriod = 0.7f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ClampMin=0.3, ClampMax=1.0f))
	float CanMoveTimer = 0.3f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float StaminaCost = 10;

	UPROPERTY(EditDefaultsOnly)
	bool bUseStaminaRegainCd = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float JumpTime = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float JumpSpeed = 10;

	UFUNCTION(BlueprintImplementableEvent)
	void PlaySound();

	
	void JumpForward(float DeltaTime);

	float JumpDelta = 0;
	float MontageDuration = 0;
	int CurrentCombo = 0;
	bool bIsAttacking = false;
	float ChainTimer;
	float LastComboCooldownTimer;
	bool bIsOnCooldown = false;

	/// TESTING
	bool testbool = false;
	

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void Activate() override;

	UPROPERTY()
	TArray<AActor*> ActorsToIgnore;
	UPROPERTY()
	APlayerCharacter* PlayerRef;

	// Functions
	void FirstHit();
	void SecondHit();
	void ThirdHit();
	void HandleChainComboTime(float DeltaTime);
	void CheckHit(bool Hit, TArray<FHitResult> HitArray);
	void HandlePlayerMovement(bool StopMovement);
	bool CanChain();
	void CheckCooldown(float DeltaTime);
	void DealDamage(UHealthComponent* HealthComponent);
};
