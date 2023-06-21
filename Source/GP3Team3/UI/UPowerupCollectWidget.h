// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Animation/WidgetAnimation.h"
#include "UPowerupCollectWidget.generated.h"


class UImage;
class UTextBlock;

/**
 * 
 */
UCLASS()
class GP3TEAM3_API UPowerupCollectWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void StartPowerUpAnimation(FText PowerUpName, FText PowerUpDescription, UTexture2D* PowerUpSprite);

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UImage* PowerUpImg;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* PowerUpNameTxt;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* PowerUpDescTxt;

	UPROPERTY( Transient, meta = ( BindWidgetAnim ) )
	UWidgetAnimation* PowerUpAnimation;

protected:
	FTimerHandle DestroyHandle;

	void DestroyPowerUpWidget();
};
