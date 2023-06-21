// Fill out your copyright notice in the Description page of Project Settings.


#include "UMetaShopWidget.h"

#include "UMetaShopEntry.h"

void UMetaShopWidget::RefreshWholeUpgradeList()
{
	TArray<UUserWidget*> AllListItems = UpgradeTileView->GetDisplayedEntryWidgets();

	for(auto Index{0}; Index < AllListItems.Num(); Index++)
	{
		UMetaShopEntry* MetaItem = Cast<UMetaShopEntry>(AllListItems[Index]);

		MetaItem->RefreshWidget();
	}
}

void UMetaShopWidget::NativeConstruct()
{
	Super::NativeConstruct();

	for (auto Index{0}; Index <= AllMetaItems.Num() - 1; Index++)
	{
		UMetaItem* NewListItem = NewObject<UMetaItem>(this, AllMetaItems[Index]->GetFName(), RF_NoFlags, AllMetaItems[Index]->GetDefaultObject());
		
		UpgradeTileView->AddItem(NewListItem);
	}

	
}
