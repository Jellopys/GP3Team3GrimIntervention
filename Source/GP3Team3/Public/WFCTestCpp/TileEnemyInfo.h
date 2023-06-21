// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/BoxComponent.h"
#include "TileEnemyInfo.generated.h"


UCLASS()
class GP3TEAM3_API UTileEnemyInfo : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTileEnemyInfo();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Tile Setup")
	bool CanTrapUntilEnemiesKilled;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
