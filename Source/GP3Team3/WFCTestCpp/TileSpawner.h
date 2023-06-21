// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BossTile.h"
#include "Sector.h"
#include "TileBase.h"
#include "TArray2D.h"
#include "GameFramework/Actor.h"
#include "TileSpawner.generated.h"

UCLASS()
class GP3TEAM3_API ATileSpawner : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATileSpawner();
	
	UFUNCTION(BlueprintCallable)
	void GenerateGrid(const FVector CenteredLocation, const int X, const int Y, const float TileSpacing);

	UFUNCTION(BlueprintCallable)
	void CollapseFirstTile();

	UFUNCTION(BlueprintCallable)
	void CollapseNextTile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<TSubclassOf<ATileBase>> AllTileClasses;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<ATileBase> SpawnTileClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<ABossTile> BossTileClass;
 	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector2D GridSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ASector> SectorClass;
	
	//TArray<TArray<TObjectPtr<ASector>>> GridSectors;
	TArray2D<TObjectPtr<ASector>> GridSectors;

	ABossTile* BossTile;
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
