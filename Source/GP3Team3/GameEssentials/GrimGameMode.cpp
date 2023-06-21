#include "GrimGameMode.h"

#include "GrimGameInstance.h"
#include "GP3Team3/UI/UMiniMapEntry.h"
#include "Kismet/GameplayStatics.h"

AGrimGameMode::AGrimGameMode()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AGrimGameMode::UnlockAuraPowerups()
{
	for (auto Index {0}; Index <= AuraPowerups.Num() - 1; Index++)
	{
		AllPowerups.Add(AuraPowerups[Index]);
	}
}

void AGrimGameMode::UnlockDashPowerups()
{
	for (auto Index {0}; Index <= DashPowerups.Num() - 1; Index++)
	{
		AllPowerups.Add(DashPowerups[Index]);
	}
}

void AGrimGameMode::AddLevelCurrency(int AddCurrency)
{
	LevelCurrency += AddCurrency;
}

void AGrimGameMode::AddCurrencyToMeta()
{
	GrimGameInstance->AddCurrency(LevelCurrency);
}

void AGrimGameMode::SpendLevelCurrency(int SpendCurrency)
{
	if (LevelCurrency < SpendCurrency)
	{
		return;
	}
	LevelCurrency -= SpendCurrency;
}

void AGrimGameMode::RegisterTileExploration(int XPos, int YPos, EExplorationState ExplorationState)
{
	if(MiniMapArray2D.Num() < 1)
	{
		return;
	}
	
	switch (ExplorationState)
	{
	case EExplorationState::Explored:

		if(MiniMapArray2D.GetElement(XPos, YPos)->CurrentExplorationState != EExplorationState::Cleared)
		{
			MiniMapArray2D.GetElement(XPos, YPos)->MapTileImg->SetBrushFromTexture(ExploredSprite);
			TilesExplored++;
			OnTileExplored();

			MiniMapArray2D.GetElement(XPos, YPos)->CurrentExplorationState = EExplorationState::Explored;
		}
		
		break;

	case EExplorationState::Cleared:

		MiniMapArray2D.GetElement(XPos, YPos)->MapTileImg->SetBrushFromTexture(ClearedSprite);
		TilesCleared++;
		OnTileCleared();

		CurrentDifficulty++;

		MiniMapArray2D.GetElement(XPos, YPos)->CurrentExplorationState = EExplorationState::Cleared;
		
		break;

	default:
		return;
	}
}

void AGrimGameMode::InitializeMiniMapArray(TArray<UUserWidget*> TileViewArray)
{
	if(TileViewArray.Num() < 1)
	{
		return;
	}
	
	UMiniMapEntry* EmptyItem;
	MiniMapArray2D.Init({EmptyItem}, 10, 10);

	for (auto OuterIndex{0}; OuterIndex <= 9; OuterIndex++)
	{
		for (auto InnerIndex{0}; InnerIndex <= 9; InnerIndex++)
		{
			UMiniMapEntry* TempEntry = Cast<UMiniMapEntry>(TileViewArray[OuterIndex*10+InnerIndex]);
			
			MiniMapArray2D.SetElement(OuterIndex, InnerIndex, TempEntry);
		}
	}
}

void AGrimGameMode::BeginPlay()
{
	Super::BeginPlay();
	GrimGameInstance = Cast<UGrimGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
}

