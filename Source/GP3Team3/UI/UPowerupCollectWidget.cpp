// Fill out your copyright notice in the Description page of Project Settings.

#include "UPowerupCollectWidget.h" 

#include "Components/Image.h"
#include "Components/TextBlock.h"


void UPowerupCollectWidget::StartPowerUpAnimation(FText PowerUpName, FText PowerUpDescription, UTexture2D* PowerUpSprite)
{
	PowerUpImg->SetBrushFromTexture(PowerUpSprite);
	PowerUpNameTxt->SetText(PowerUpName);
	PowerUpDescTxt->SetText(PowerUpDescription);

	PlayAnimation(PowerUpAnimation);

	FTimerDelegate Delegate;
	Delegate.BindUObject(this, &UPowerupCollectWidget::DestroyPowerUpWidget);
	GetWorld()->GetTimerManager().SetTimer(DestroyHandle, Delegate, PowerUpAnimation->GetEndTime() + 1.f, false);
}

void UPowerupCollectWidget::DestroyPowerUpWidget()
{
	RemoveFromParent();
}
