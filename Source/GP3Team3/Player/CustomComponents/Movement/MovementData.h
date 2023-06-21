// Richard Hill - FutureGames

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MovementData.generated.h"


UCLASS()
class UMovementData : public UDataAsset
{
	GENERATED_BODY()

public:
	// The top horizontal speed the character can reach, in U/s.
	UPROPERTY(EditAnywhere, Category = "Speed")
	float MoveSpeed;
	// How many U/s the speed increases by when moving.
	UPROPERTY(EditAnywhere, Category = "Speed", meta=(ClampMin="0.0"))
	float Acceleration;
	// The vertical speed applied when pressing the jump button.

	// The downwards acceleration applied when in mid-air, in U/s2.
	UPROPERTY(EditAnywhere, Category = "Speed")
	float Gravity;
	
};
