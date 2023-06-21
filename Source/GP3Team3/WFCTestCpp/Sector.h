// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TileBase.h"
#include "GameFramework/Actor.h"
#include "Sector.generated.h"

UCLASS()
class GP3TEAM3_API ASector : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASector();

	void Collapse();
	void Collapse(TSubclassOf<ATileBase> SpawnTileClass);

	void FilterPossibleList(TArray<ETileType> TileTypesToKeep, TObjectPtr<ASector> PreviousSector);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<TSubclassOf<ATileBase>> PossibleTileClasses;
	TObjectPtr<ATileBase> GeneratedTile;
	TSubclassOf<ATileBase> GeneratedTileClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int XPos;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int YPos;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<ATileBase> NullTileClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = true))
	USceneComponent* SceneRoot;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
