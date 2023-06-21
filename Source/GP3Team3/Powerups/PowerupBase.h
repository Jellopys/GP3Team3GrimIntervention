// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GP3Team3/Player/PlayerCharacter.h"
#include "UObject/Object.h"
#include "PowerupBase.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class GP3TEAM3_API UPowerupBase : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PowerUp Info")
	FText PowerupName;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PowerUp Info")
	FText PowerupDescription;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PowerUp Info")
	UTexture2D* PowerupImage;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	APlayerCharacter* PlayerCharacter;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	AGrimGameMode* GameMode;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UGrimGameInstance* GameInstance;

	void RegisterPowerUp(APlayerCharacter* PlayerC, AGrimGameMode* GameM, UGrimGameInstance* GameI);
	
	UFUNCTION(BlueprintImplementableEvent, Category = "Powerup Events")
	void OnPowerUpGotten();
};
