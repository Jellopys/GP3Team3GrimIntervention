// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "USaveFile.generated.h"

/**
 * 
 */
UCLASS()
class GP3TEAM3_API USaveFile : public USaveGame
{
	GENERATED_BODY()
public:
	USaveFile();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int CurrencyBalance;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int CurrencySpent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int MetaMaxHealthUpgrades;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int MetaSpeedUpgrades;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int MetaMaxStaminaUpgrades;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int MetaDashDistanceUpgrades;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int MetaLuckUpgrades;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int MetaDamageUpgrades;
};
