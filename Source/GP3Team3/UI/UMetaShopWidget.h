// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MetaItem.h"
#include "Blueprint/UserWidget.h"
#include "Animation/WidgetAnimation.h"
#include "Components/TileView.h"
#include "UMetaShopWidget.generated.h"


class UImage;
class UTextBlock;

/**
 * 
 */
UCLASS(Abstract)
class GP3TEAM3_API UMetaShopWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<TSubclassOf<UMetaItem>> AllMetaItems;
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTileView* UpgradeTileView;

	UFUNCTION(BlueprintCallable)
	void RefreshWholeUpgradeList();

protected:
	virtual void NativeConstruct() override;
};
