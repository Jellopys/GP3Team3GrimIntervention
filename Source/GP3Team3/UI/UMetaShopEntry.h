#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "UMetaShopEntry.generated.h"

class UTextBlock;
class UImage;

UCLASS(Abstract)
class UMetaShopEntry : public UUserWidget, public IUserObjectListEntry
{
private:
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void RefreshWidget();
	
protected:
	// IUserObjectListEntry
	virtual void NativeOnListItemObjectSet(UObject* MetaItem) override;
	// IUserObjectListEntry

	class UGrimGameInstance* GameInstance;
	class UMetaItem* Item;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UTexture2D* EmptyIndicator;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UTexture2D* FullIndicator;
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnUpgradeBought();
	
	UPROPERTY(meta=(BindWidget))
	UTextBlock* NameLabel;
	
	UPROPERTY(meta=(BindWidget))
	UTextBlock* CostLabel;

	UPROPERTY(meta=(BindWidget))
	UImage* IconImage;

	UPROPERTY(meta=(BindWidget))
	class UButton* BuyButton;

	UPROPERTY(meta=(BindWidget))
	UImage* indicator1;
	UPROPERTY(meta=(BindWidget))
	UImage* indicator2;
	UPROPERTY(meta=(BindWidget))
	UImage* indicator3;
	UPROPERTY(meta=(BindWidget))
	UImage* indicator4;
	UPROPERTY(meta=(BindWidget))
	UImage* indicator5;

	TArray<UImage*> Indicators;

	UFUNCTION()
	void BuyUpgrade();
};

