// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TileType.h"
#include "GameFramework/Actor.h"
#include "GP3Team3/Public/WFCTestCpp/TileEnemyInfo.h"
#include "TileBase.generated.h"

class ALootSpawner;

UCLASS()
class GP3TEAM3_API ATileBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATileBase();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Setup")
	ETileType ThisTileType;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<ETileType> Up_TypeConnections;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<ETileType> Down_TypeConnections;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<ETileType> Left_TypeConnections;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<ETileType> Right_TypeConnections;

	void RegisterEnemyKill();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int XPos;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int YPos;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Enemy")
	TArray<AActor*> EnemySpawners;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	class AGrimGameMode* GameMode;

	FTileTypeArrays* ArrayDictionary;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = true))
	USceneComponent* SceneRoot;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = true))
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = true))
	TObjectPtr<UTileEnemyInfo> TileEnemyInfoComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = true))
	TObjectPtr<UBoxComponent> TileOverlapBox;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Setup")
	TSubclassOf<AActor> FightWallClass;
	
	AActor* UpWall;
	AActor* DownWall;
	AActor* LeftWall;
	AActor* RightWall;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void SpawnLoot();
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Enemy")
	TArray<ALootSpawner*> LootSpawners;

	int NumberOfAliveEnemies;

	bool WallsUp;

	int GetNumberOfEnemiesToSpawn();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	bool PlayerHasEnteredTile;
};
