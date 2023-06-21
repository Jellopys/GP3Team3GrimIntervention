// Richard Hill

#pragma once

#include "BaseSpell.h"
#include "CastProjectile.generated.h"

class AForwardProjectile;
class ABaseEnemy;

UCLASS()
class GP3TEAM3_API ACastProjectile : public ABaseSpell
{
	GENERATED_BODY()

public:
	ACastProjectile();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* CastMontage;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ForwardSpawnPosLength = 100;
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
	TSubclassOf<AForwardProjectile> Projectile;
	
	float CachedChargeUpTime = 0.5f;
	float CachedChargeTime = 1;
	bool bIsAttacking = false;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void Activate() override;
	void RotateTowardPlayer(float DeltaTime);
	void ReleaseProjectile();

	UPROPERTY()
	APlayerCharacter* PlayerRef;
	UPROPERTY()
	ABaseEnemy* BaseEnemy;
};
