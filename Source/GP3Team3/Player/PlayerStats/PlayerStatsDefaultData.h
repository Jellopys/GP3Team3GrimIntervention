// Richard Hill - FutureGames

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PlayerStatsDefaultData.generated.h"


UCLASS()
class UPlayerStatsDefaultData : public UDataAsset
{
	GENERATED_BODY()

public:
	// Movement
	UPROPERTY(EditAnywhere, Category = Movement)
	float MovementSpeed = 500;

	// Stamina
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stamina)
	float MaxStamina = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stamina)
	float CurrentStamina = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stamina)
	float StaminaGainMultiplier = 10;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stamina)
	float StaminaRegainTime = 2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stamina)	
	float ScytheTossStaminaCost = 20;

	// Dash
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dash)
	float DashPower = 50;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dash)
	float DashCooldown = 0.5f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dash)
	float DashDuration = 0.2f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dash)
	float DashStaminaCost = 20;

	//Dash Combat
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DashCombat)	
	float DashDamage = 1;
	
	// Health
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dash)
	float MaxHealth = 10;
	
	// Combat
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat)
	float FirstComboDamage = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat)
	float SecondComboDamage = 2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat)
	float ThirdComboDamage = 3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat)
	float AttackSpeed = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat)
	float BaseDamageMultiplier = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat)
	float AttackRangeMultiplier = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat)	
	float ScytheTossDamage = 4;

	//Crit
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Crit)
	float CritChance = 5;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Crit)
	float CritDamage = 10;
};
