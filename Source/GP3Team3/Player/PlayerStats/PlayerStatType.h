// Richard Hill

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EPlayerStatType : uint8 {
	MovementSpeed = 0				UMETA(DisplayName = "Movement Speed"),
	MaxStamina = 1					UMETA(DisplayName = "Max Stamina"),
	StaminaGainMultiplier = 2		UMETA(DisplayName = "Stamina Gain Multiplier"),
	StaminaRegainTime = 3			UMETA(DisplayName = "Stamina Regain Time"),
	DashPower = 4					UMETA(DisplayName = "Dash Power"),
	MaxHealth = 5					UMETA(DisplayName = "Max Health"),
	FirstComboDamage = 6			UMETA(DisplayName = "First Combo Damage"),
	SecondComboDamage = 7			UMETA(DisplayName = "Second Combo Damage"),
	ThirdComboDamage = 8			UMETA(DisplayName = "Third Combo Damage"),
	AttackSpeed = 9					UMETA(DisplayName = "Attack Speed"),
	DashStaminaCost = 10			UMETA(DisplayName = "Dash Stamina Cost"),
	BaseDamageMultiplier = 11		UMETA(DisplayName = "Base Damage Multiplier"),
	AttackRangeMultiplier = 12		UMETA(DisplayName = "Attack Range Multiplier"),
	ScytheTossStaminaCost = 13		UMETA(DisplayName = "Scythe Toss Stamina Cost"),
	ScytheTossDamage = 14			UMETA(DisplayName = "Scythe Toss Damage"),
	DashDamage = 15					UMETA(DisplayName = "Reaper Dash Damage"),
	CritChance = 16					UMETA(DisplayName = "Crit Chance"),
	CritDamage = 17					UMETA(DisplayName = "Crit Damage")
};