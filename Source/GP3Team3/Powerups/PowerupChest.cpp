// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerupChest.h"

#include "Blueprint/UserWidget.h"
#include "GP3Team3/GameEssentials/GrimGameInstance.h"
#include "GP3Team3/UI/UPowerupCollectWidget.h"
#include "Kismet/GameplayStatics.h"
#include "UI/OpenChestWidget.h"


// Sets default values
APowerupChest::APowerupChest()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void APowerupChest::OpenChest()
{
	if(HasOpened)
	{
		return;
	}

	GameModeRef = Cast<AGrimGameMode>(GetWorld()->GetAuthGameMode());
	GameInstanceRef = Cast<UGrimGameInstance>(GetWorld()->GetGameInstance());
	APawn* Character = (UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	PlayerRef = Cast<APlayerCharacter>(Character);

	HasOpened = true;
	
	//Present a random power-up
	if(GameModeRef->AllPowerups.Num()>1)
	{
		TArray<TSubclassOf<UPowerupBase>> TempAllPowerups = GameModeRef->AllPowerups;
		
		int IndexPicker = FMath::RandRange(0, TempAllPowerups.Num()-1);

		item_class = TempAllPowerups[IndexPicker];
		UPowerupBase* item = NewObject<UPowerupBase>(this, item_class);
		TempAllPowerups.Remove(item_class);
		
		SelectedPowerup = item;

		OpenChestWidget = CreateWidget<UOpenChestWidget>(UGameplayStatics::GetPlayerController(GetWorld(), 0), ChestOpenWidgetClass);
		OpenChestWidget->AddToViewport(9999);
		
		OpenChestWidget->PowerupImg->SetBrushFromTexture(SelectedPowerup->PowerupImage);
		OpenChestWidget->PowerupName->SetText(SelectedPowerup->PowerupName);
		OpenChestWidget->PowerupDescTxt->SetText(SelectedPowerup->PowerupDescription);

		OpenChestWidget->OwningChest = this;

		IndexPicker = FMath::RandRange(0, TempAllPowerups.Num()-1);

		item_class2 = TempAllPowerups[IndexPicker];
		UPowerupBase* item2 = NewObject<UPowerupBase>(this, item_class2);
		TempAllPowerups.Remove(item_class2);
		
		SelectedPowerup2 = item2;
		
		OpenChestWidget->PowerupImg2->SetBrushFromTexture(SelectedPowerup2->PowerupImage);
		OpenChestWidget->PowerupName2->SetText(SelectedPowerup2->PowerupName);
		OpenChestWidget->PowerupDescTxt2->SetText(SelectedPowerup2->PowerupDescription);
		
		GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);

		OnChestOpen();
	}

	//Present one PU & one Stat-up
	else if(GameModeRef->AllPowerups.Num() == 1)
	{
		TArray<TSubclassOf<UPowerupBase>> TempAllPowerups = GameModeRef->AllPowerups;
		
		int IndexPicker = FMath::RandRange(0, TempAllPowerups.Num()-1);

		item_class = TempAllPowerups[IndexPicker];
		UPowerupBase* item = NewObject<UPowerupBase>(this, item_class);
		TempAllPowerups.Remove(item_class);
		
		SelectedPowerup = item;

		OpenChestWidget = CreateWidget<UOpenChestWidget>(UGameplayStatics::GetPlayerController(GetWorld(), 0), ChestOpenWidgetClass);
		OpenChestWidget->AddToViewport(9999);
		
		OpenChestWidget->PowerupImg->SetBrushFromTexture(SelectedPowerup->PowerupImage);
		OpenChestWidget->PowerupName->SetText(SelectedPowerup->PowerupName);
		OpenChestWidget->PowerupDescTxt->SetText(SelectedPowerup->PowerupDescription);

		OpenChestWidget->OwningChest = this;

		IndexPicker = FMath::RandRange(0, GameModeRef->AllStatups.Num()-1);

		item_class2 = GameModeRef->AllStatups[IndexPicker];
		UPowerupBase* item2 = NewObject<UPowerupBase>(this, item_class2);
		
		SelectedPowerup2 = item2;
		
		OpenChestWidget->PowerupImg2->SetBrushFromTexture(SelectedPowerup2->PowerupImage);
		OpenChestWidget->PowerupName2->SetText(SelectedPowerup2->PowerupName);
		OpenChestWidget->PowerupDescTxt2->SetText(SelectedPowerup2->PowerupDescription);
		
		GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);

		OnChestOpen();
	}

	//Present money & Stat-up
	else
	{
		int IndexPicker = FMath::RandRange(0, GameModeRef->AllMoneyups.Num()-1);

		item_class = GameModeRef->AllMoneyups[IndexPicker];
		UPowerupBase* item = NewObject<UPowerupBase>(this, item_class);
		
		SelectedPowerup = item;

		OpenChestWidget = CreateWidget<UOpenChestWidget>(UGameplayStatics::GetPlayerController(GetWorld(), 0), ChestOpenWidgetClass);
		OpenChestWidget->AddToViewport(9999);
		
		OpenChestWidget->PowerupImg->SetBrushFromTexture(SelectedPowerup->PowerupImage);
		OpenChestWidget->PowerupName->SetText(SelectedPowerup->PowerupName);
		OpenChestWidget->PowerupDescTxt->SetText(SelectedPowerup->PowerupDescription);

		OpenChestWidget->OwningChest = this;

		IndexPicker = FMath::RandRange(0, GameModeRef->AllStatups.Num()-1);

		item_class2 = GameModeRef->AllStatups[IndexPicker];
		UPowerupBase* item2 = NewObject<UPowerupBase>(this, item_class2);
		
		SelectedPowerup2 = item2;
		
		OpenChestWidget->PowerupImg2->SetBrushFromTexture(SelectedPowerup2->PowerupImage);
		OpenChestWidget->PowerupName2->SetText(SelectedPowerup2->PowerupName);
		OpenChestWidget->PowerupDescTxt2->SetText(SelectedPowerup2->PowerupDescription);
		
		GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);

		OnChestOpen();
	}
}

void APowerupChest::TakePowerup()
{
	SelectedPowerup->RegisterPowerUp(PlayerRef, GameModeRef, GameInstanceRef);

	OpenChestWidget->RemoveFromParent();
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(false);

	UPowerupCollectWidget* PowerupCollectWidget = CreateWidget<UPowerupCollectWidget>(UGameplayStatics::GetPlayerController(GetWorld(), 0), GameModeRef->PowerUpWidgetClass);
	PowerupCollectWidget->AddToViewport(9999);
	PowerupCollectWidget->StartPowerUpAnimation(SelectedPowerup->PowerupName, SelectedPowerup->PowerupDescription, SelectedPowerup->PowerupImage);

	if(GameModeRef->AllPowerups.Contains(item_class))
	{
		GameModeRef->AllPowerups.Remove(item_class);
	}
	
	OnChestClose();
}

void APowerupChest::TakePowerup2()
{
	SelectedPowerup2->RegisterPowerUp(PlayerRef, GameModeRef, GameInstanceRef);

	OpenChestWidget->RemoveFromParent();
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(false);

	UPowerupCollectWidget* PowerupCollectWidget = CreateWidget<UPowerupCollectWidget>(UGameplayStatics::GetPlayerController(GetWorld(), 0), GameModeRef->PowerUpWidgetClass);
	PowerupCollectWidget->AddToViewport(9999);
	PowerupCollectWidget->StartPowerUpAnimation(SelectedPowerup2->PowerupName, SelectedPowerup2->PowerupDescription, SelectedPowerup2->PowerupImage);

	if(GameModeRef->AllPowerups.Contains(item_class2))
	{
		GameModeRef->AllPowerups.Remove(item_class2);
	}
	
	OnChestClose();
}

// Called when the game starts or when spawned
void APowerupChest::BeginPlay()
{
	Super::BeginPlay();

	GameModeRef = Cast<AGrimGameMode>(GetWorld()->GetAuthGameMode());
	GameInstanceRef = Cast<UGrimGameInstance>(GetWorld()->GetGameInstance());
	APawn* Character = (UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	PlayerRef = Cast<APlayerCharacter>(Character);
}

// Called every frame
void APowerupChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

