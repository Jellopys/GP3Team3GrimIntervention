// Richard Hill

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EAIState : uint8 {
	Patrol = 0					UMETA(DisplayName = "Patrol"),
	Chase = 1					UMETA(DisplayName = "Chase"),
	Flank = 2					UMETA(DisplayName = "Flank"),
	Attack = 3					UMETA(DisplayName = "Attack"),
	AttackSuccession = 4		UMETA(DisplayName = "AttackSuccession"),
	AssessRange = 5				UMETA(DisplayName = "AssessRange"),
	AttackTwo = 6				UMETA(DisplayName = "AttackTwo"),
	Exhausted = 7				UMETA(DisplayName = "Exhausted"),
	ChargeUp = 8				UMETA(DisplayName = "ChargeUp"),
	AttackThree = 9				UMETA(DisplayName = "AttackThree"),
	AttackFour = 10				UMETA(DisplayName = "AttackFour"),
};