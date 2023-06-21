// Fill out your copyright notice in the Description page of Project Settings.


#include "UMiniMapWidget.h"

#include "Components/Image.h"
#include "GP3Team3/GameEssentials/GrimGameMode.h"

void UMiniMapWidget::NativeConstruct()
{
	Super::NativeConstruct();

	for (auto Index{0}; Index < 100; Index++)
	{
		UObject* NewListItem = NewObject<UUMapItem>(this, FName(*FString::FromInt(Index)), RF_NoFlags, MapItem->GetDefaultObject());
		
		MapTileView->AddItem(NewListItem);
	}
}
