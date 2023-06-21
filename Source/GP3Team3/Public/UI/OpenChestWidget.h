// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "GP3Team3/Powerups/PowerupChest.h"
#include "OpenChestWidget.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class GP3TEAM3_API UOpenChestWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	APowerupChest* OwningChest;
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UImage* PowerupImg;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* PowerupName;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* PowerupDescTxt;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UImage* PowerupImg2;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* PowerupName2;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* PowerupDescTxt2;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* TakeBtn;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* DiscardBtn;

	virtual void NativeConstruct() override;

protected:
	UFUNCTION()
	void Take();
	UFUNCTION()
	void Discard();
};
