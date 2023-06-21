// Richard Hill

#pragma once

#include "GameFramework/Actor.h"
#include "CollisionShape.h"
#include "ScytheProjectile.generated.h"

class USphereComponent;
class UStaticMeshComponent;
class APlayerCharacter;

UCLASS()
class AScytheProjectile : public AActor
{
	GENERATED_BODY()

public:
	AScytheProjectile();
	UFUNCTION(BlueprintImplementableEvent)
	void OnActive();
	UFUNCTION(BlueprintImplementableEvent)
	void OnHit();
	UFUNCTION(BlueprintCallable)
	void AssignParent(AActor* NewParent);
	UFUNCTION(BlueprintCallable)
	void SetActiveStatus(bool SetActive);
	UFUNCTION(BlueprintImplementableEvent)
	void OnScytheCast();
	UFUNCTION(BlueprintImplementableEvent)
	void OnScytheReturn();
	UFUNCTION(BlueprintImplementableEvent)
	void OnScytheReachApex();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USphereComponent* Sphere;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Mesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float StopDistance = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TravelDistance = 1000;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TravelSpeed = 100.f;
	UPROPERTY(EditAnywhere)
	float MaxLifeTime = 5.0f;

	UPROPERTY()
	AActor* Parent;
	UPROPERTY()
	APlayerCharacter* PlayerRef;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void ReturnScythe(float DeltaTime);
	void MoveProjectile(float DeltaTime);
	

	FVector TargetLocation = FVector::ZeroVector;
	FVector OriginLocation = FVector::ZeroVector;
	bool bReturnScythe = false;
	float TravelDelta = 0;
	bool bIsActive = false;
	float ScytheForwardSpawnLoc = 100;
	
	UPROPERTY()
	TArray<AActor*> IgnoreList;
	float LifeTime = 0;
};
