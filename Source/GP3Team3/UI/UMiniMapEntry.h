// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "GP3Team3/GameEssentials/GrimGameMode.h"
#include "UMiniMapEntry.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class GP3TEAM3_API UMiniMapEntry : public UUserWidget, public IUserObjectListEntry
{

	GENERATED_BODY()
	
public:

	EExplorationState CurrentExplorationState;
	
	UPROPERTY(meta = (BindWidget))
	UImage* MapTileImg;

protected:
	virtual void NativeOnListItemObjectSet(UObject* MiniMapItem) override;
};
