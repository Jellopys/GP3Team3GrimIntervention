// Fill out your copyright notice in the Description page of Project Settings.


#include "UMetaShopEntry.h"

#include "MetaItem.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "GP3Team3/GameEssentials/GrimGameInstance.h"
#include "Kismet/GameplayStatics.h"

void UMetaShopEntry::NativeOnListItemObjectSet(UObject* MetaItem)
{
	GameInstance = Cast<UGrimGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	
	Item = Cast<UMetaItem>(MetaItem);
	NameLabel->SetText(Item->DisplayName);
	IconImage->SetBrushFromTexture(Item->Icon);

	Indicators.Empty();
	Indicators.Add(indicator1);
	Indicators.Add(indicator2);
	Indicators.Add(indicator3);
	Indicators.Add(indicator4);
	Indicators.Add(indicator5);
	
	//Bind Buy Button
	BuyButton->OnClicked.AddDynamic(this, &UMetaShopEntry::BuyUpgrade);
	
	RefreshWidget();
}

void UMetaShopEntry::BuyUpgrade()
{
	//If upgrade is not maxed out... (Not Bought 5 times)
	
	if(GameInstance->GetMetaUpgradeTimesBought(Item->UpgradeType) < 5 && Item->BaseCost + (Item->ExtraCostPerUpgrade * GameInstance->GetMetaUpgradeTimesBought(Item->UpgradeType)) <= GameInstance->CurrencyBalance)
	{
		GameInstance->SpendCurrency(Item->BaseCost + (Item->ExtraCostPerUpgrade * GameInstance->GetMetaUpgradeTimesBought(Item->UpgradeType)));
		GameInstance->UpgradeMetaStat(Item->UpgradeType);

		OnUpgradeBought();
		
		RefreshWidget();
	}
}

void UMetaShopEntry::RefreshWidget()
{
	if(GameInstance->GetMetaUpgradeTimesBought(Item->UpgradeType) < 5)
	{
		int CalculatedCost = Item->BaseCost + (Item->ExtraCostPerUpgrade * GameInstance->GetMetaUpgradeTimesBought(Item->UpgradeType));
	
		CostLabel->SetText(FText::FromString(FString::FromInt(CalculatedCost)));

		for (auto Index{0}; Index < Indicators.Num(); Index++)
		{
			if(Index < GameInstance->GetMetaUpgradeTimesBought(Item->UpgradeType))
			{
				Indicators[Index]->SetBrushFromTexture(FullIndicator);
			}
			else
			{
				Indicators[Index]->SetBrushFromTexture(EmptyIndicator);
			}
			
		}
	}
	
	else
	{
		CostLabel->SetText(FText::FromString(TEXT("MAX")));

		for (auto Index{0}; Index < Indicators.Num(); Index++)
		{
			Indicators[Index]->SetBrushFromTexture(FullIndicator);
		}
	}
}
