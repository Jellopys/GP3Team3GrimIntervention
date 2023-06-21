// Richard Hill

#pragma once

#include "BaseSpell.h"
#include "Spell_Pounce.generated.h"

UCLASS()
class ASpell_Pounce : public ABaseSpell
{
	GENERATED_BODY()

public:
	ASpell_Pounce();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ChargeSpeed = 10;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ChargeTime = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ChargeUpTime = 0.5f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FakeLerp = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ChargeUpTurnRate = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SphereRadius = 50;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ForwardSweepRange = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float PlayerFuturePosDeltaFrames = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DebugDrawTime = 1;
	
	float CachedChargeUpTime = 0.5f;
	float CachedChargeTime = 1;
	bool bIsAttacking = false;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void Activate() override;

	void ResetTimers();
	void PounceForward(float DeltaTime);
	void RotateTowardPlayer(float DeltaTime);
	void SweepForward();
	void CheckHit(bool Hit, TArray<FHitResult> HitArray);
	
	UPROPERTY()
	TArray<AActor*> ActorsToIgnore;
	UPROPERTY()
	AActor* IgnoreActor;
	
	bool bIsCharging = false;
	FVector ChargePos;
	
	UPROPERTY()
	APlayerCharacter* PlayerRef;
};
