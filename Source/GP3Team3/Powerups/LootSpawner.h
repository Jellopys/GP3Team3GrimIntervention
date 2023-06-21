#pragma once

#include "CoreMinimal.h"
#include "PowerupChest.h"
#include "GameFramework/Actor.h"
#include "LootSpawner.generated.h"

UCLASS()
class GP3TEAM3_API ALootSpawner : public AActor
{
	GENERATED_BODY()

public:
	ALootSpawner();

	void SpawnLoot();
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnLootSpawned();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Setup")
	TSubclassOf<APowerupChest> ChestClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Setup")
	TSubclassOf<AActor> SoulClass;

protected:
	virtual void BeginPlay() override;
};
