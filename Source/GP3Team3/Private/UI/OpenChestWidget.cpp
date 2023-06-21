// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/OpenChestWidget.h"

void UOpenChestWidget::NativeConstruct()
{
	Super::NativeConstruct();

	TakeBtn->OnClicked.AddDynamic(this, &UOpenChestWidget::Take);
	DiscardBtn->OnClicked.AddDynamic(this, &UOpenChestWidget::Discard);
}

void UOpenChestWidget::Take()
{
	OwningChest->TakePowerup();
}

void UOpenChestWidget::Discard()
{
	OwningChest->TakePowerup2();
}
