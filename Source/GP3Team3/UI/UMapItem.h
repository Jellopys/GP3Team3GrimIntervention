// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "UMapItem.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class GP3TEAM3_API UUMapItem : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UTexture2D* MapItemSprite;
};
