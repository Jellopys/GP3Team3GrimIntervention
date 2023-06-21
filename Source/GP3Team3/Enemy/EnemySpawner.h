#pragma once

#include "CoreMinimal.h"
#include "BaseEnemy.h"
#include "GameFramework/Actor.h"
#include "EnemySpawner.generated.h"

class ATileBase;

UCLASS()
class GP3TEAM3_API AEnemySpawner : public AActor
{
	GENERATED_BODY()

public:
	AEnemySpawner();
	
	void SpawnEnemy();

	UFUNCTION(BlueprintImplementableEvent)
	void OnEnemySpawned();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<AActor>> EnemyClasses;
	
	TSubclassOf<AActor> GetRandomEnemyClass();
	
protected:
	virtual void BeginPlay() override;
};
