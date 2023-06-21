// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "MetaItem.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EMetaUpgradeType : uint8 {
	MaxHealth = 0 UMETA(DisplayName = "MAX HEALTH"),
	MaxStamina = 1  UMETA(DisplayName = "MAX STAMINA"),
	DashDistance = 2     UMETA(DisplayName = "DASH DISTANCE"),
	Speed = 3  UMETA(DisplayName = "SPEED"),
	Luck = 4  UMETA(DisplayName = "LUCK"),
	Damage = 5  UMETA(DisplayName = "DAMAGE")
};

UCLASS(Blueprintable, BlueprintType)
class GP3TEAM3_API UMetaItem : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EMetaUpgradeType UpgradeType;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText DisplayName;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UTexture2D* Icon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int BaseCost;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int ExtraCostPerUpgrade;
};
