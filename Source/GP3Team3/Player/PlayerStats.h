#pragma once

#include "CoreMinimal.h"
#include "PlayerStats.generated.h"

USTRUCT(BlueprintType)
struct FPlayerStats
{
	GENERATED_BODY()
	
	FPlayerStats();
	~FPlayerStats();
	
	//Movement & Dash
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement")
	float MovementSpeed = 500;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement")
	float DashPower = 50;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement")
	float DashCooldown = 0.5f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement")
	float DashDuration = 0.2f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category ="Movement")
	float DashStaminaCost = 20;

	//Dash Combat
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DashCombat)
	float DashDamage = 1;
	
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
	

	// Health
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= Health)
	int MaxHealth = 10;

	// Combat
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat)
	float BaseDamageMultiplier = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat)
	float FirstComboDamage = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat)
	float SecondComboDamage = 2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat)
	float ThirdComboDamage = 3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat)
	float AttackSpeed = 0.7f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat)
	float AttackRangeMultiplier = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Combat)
	float ScytheTossDamage = 4;
	
	//Crit
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Crit)
	float CritChance = 5;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Crit)
	float CritDamage = 10;

	// //Melee Attack
	// UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Melee Attack")
	// float MeleeAttackSpeed;
	// UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Melee Attack")
	// float MeleeAttackCooldown;
	//
	// //Ranged Attack
	// UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ranged Attack")
	// float RangedAttackSpeed;
	// UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ranged Attack")
	// float RangedAttackCooldown;
	//
	// //Combo
	// UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combo")
	// float ComboMultiplier;
	// UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combo")
	// float ComboTime;
	//
	// //Money
	// UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Money")
	// float MoneyMultiplier;
	// UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Money")
	// int MoneyDropOnTakingDamage;
	//
	// //Soul
	// UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Soul")
	// float SoulMultiplier;
};