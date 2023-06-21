// Fill out your copyright notice in the Description page of Project Settings.


#include "UMiniMapEntry.h"

#include "UMapItem.h"


void UMiniMapEntry::NativeOnListItemObjectSet(UObject* MiniMapItem)
{
	UUMapItem* Item = Cast<UUMapItem>(MiniMapItem);

	CurrentExplorationState = EExplorationState::Unexplored;
	
	MapTileImg->SetBrushFromTexture(Item->MapItemSprite);
}
