// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TileType.generated.h"

UENUM(BlueprintType)
enum class ETileType : uint8 {
	LevelOne = 0 UMETA(DisplayName = "LEVEL ONE"),
	LevelTwo = 1  UMETA(DisplayName = "LEFT TWO"),
	StairUp = 2     UMETA(DisplayName = "STAIR UP"),
	StairDown = 3  UMETA(DisplayName = "STAIR DOWN"),
	StairLeft = 4  UMETA(DisplayName = "STAIR LEFT"),
	StairRight = 5  UMETA(DisplayName = "STAIR RIGHT"),
	Void = 6 UMETA(DisplayName = "VOID")
};

USTRUCT(BlueprintType)
struct FTileTypeArrays
{
	GENERATED_BODY()

public:
	FTileTypeArrays();

	TArray<ETileType> LevelOneU;
	TArray<ETileType> LevelOneD;
	TArray<ETileType> LevelOneL;
	TArray<ETileType> LevelOneR;
	
	TArray<ETileType> LevelTwoU;
	TArray<ETileType> LevelTwoD;
	TArray<ETileType> LevelTwoL;
	TArray<ETileType> LevelTwoR;

	TArray<ETileType> StairUpU;
	TArray<ETileType> StairUpD;
	TArray<ETileType> StairUpL;
	TArray<ETileType> StairUpR;

	TArray<ETileType> StairDownU;
	TArray<ETileType> StairDownD;
	TArray<ETileType> StairDownL;
	TArray<ETileType> StairDownR;

	TArray<ETileType> StairLeftU;
	TArray<ETileType> StairLeftD;
	TArray<ETileType> StairLeftL;
	TArray<ETileType> StairLeftR;

	TArray<ETileType> StairRightU;
	TArray<ETileType> StairRightD;
	TArray<ETileType> StairRightL;
	TArray<ETileType> StairRightR;

	TArray<ETileType> VoidU;
	TArray<ETileType> VoidD;
	TArray<ETileType> VoidL;
	TArray<ETileType> VoidR;
};
