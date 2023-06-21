// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UMapItem.h"
#include "Components/TileView.h"
#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanel.h"
#include "UMiniMapWidget.generated.h"

class APowerupChest;

/**
 * 
 */
UCLASS(Abstract)
class GP3TEAM3_API UMiniMapWidget : public UUserWidget
{

	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UTexture2D* TreasureIcon;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UUMapItem> MapItem;
	
	UPROPERTY(EditAnywhere, meta = (BindWidget), BlueprintReadOnly)
	UTileView* MapTileView;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
	UCanvasPanel* MiniMapCanvas;

protected:
	virtual void NativeConstruct() override;
};
