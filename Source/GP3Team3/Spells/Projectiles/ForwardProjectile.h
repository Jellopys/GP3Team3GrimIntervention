// Richard Hill

#pragma once

#include "GameFramework/Actor.h"
#include "CollisionShape.h"
#include "ForwardProjectile.generated.h"

class USphereComponent;
class UStaticMeshComponent;
class ABaseEnemy;

UCLASS()
class AForwardProjectile : public AActor
{
	GENERATED_BODY()

public:
	AForwardProjectile();
	UFUNCTION(BlueprintImplementableEvent)
	void OnActive();
	UFUNCTION(BlueprintImplementableEvent)
	void OnHit();
	UFUNCTION(BlueprintCallable)
	void AssignParent(AActor* NewParent);
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USphereComponent* Sphere;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Mesh;
	UPROPERTY(EditAnywhere)
	float TravelSpeed = 100.f;
	UPROPERTY(EditAnywhere)
	float MaxLifeTime = 5.0f;
	UPROPERTY()
	ABaseEnemy* BaseEnemy;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage = 5;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsPenetrating = false;

	UPROPERTY()
	AActor* Parent;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
	void MoveProjectile(float DeltaTime);
	void SetActiveStatus(bool status);
	
	UPROPERTY()
	TArray<AActor*> IgnoreList;
	float LifeTime = 0;
};
