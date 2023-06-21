// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GP3Team3/Powerups/PowerupBase.h"
#include "GP3Team3/WFCTestCpp/TArray2D.h"
#include "GrimGameMode.generated.h"


class UPlayerStatsObject;
class UGrimGameInstance;
class UMiniMapEntry;

UENUM(BlueprintType)
enum class EExplorationState : uint8 {
	Unexplored = 0 UMETA(DisplayName = "UNEXPLORED"),
	Explored = 1  UMETA(DisplayName = "EXPLORED"),
	Cleared = 2     UMETA(DisplayName = "CLEARED")
};

UCLASS()
class AGrimGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AGrimGameMode();

	//Difficulty
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Difficulty")
	int CurrentDifficulty = 0;
	
	//Powerups
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> PowerUpWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Powerups")
	TArray<TSubclassOf<UPowerupBase>> AllPowerups;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Powerups")
	TArray<TSubclassOf<UPowerupBase>> AuraPowerups;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Powerups")
	TArray<TSubclassOf<UPowerupBase>> DashPowerups;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Powerups")
	TArray<TSubclassOf<UPowerupBase>> AllStatups;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Powerups")
	TArray<TSubclassOf<UPowerupBase>> AllMoneyups;

	UFUNCTION(BlueprintCallable)
	void UnlockAuraPowerups();
	UFUNCTION(BlueprintCallable)
	void UnlockDashPowerups();

	//Tile Temporary Stats
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Temp Stats")
	float TileTempDamage = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Temp Stats")
	float TileTempAuraDamage = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Temp Stats")
	float TileTempDashDamage = 0;

	UFUNCTION(BlueprintImplementableEvent)
	void ResetTempStats();
	
	//Level Currency
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int LevelCurrency = 0;

	UFUNCTION(BlueprintCallable)
	void AddLevelCurrency(int AddCurrency);

	UFUNCTION(BlueprintCallable)
	void AddCurrencyToMeta();

	UFUNCTION(BlueprintCallable)
	void SpendLevelCurrency(int SpendCurrency);

	//Exploration

	UFUNCTION(BlueprintImplementableEvent)
	void OnTileExplored();

	UFUNCTION(BlueprintImplementableEvent)
	void OnTileCleared();

	UFUNCTION(BlueprintImplementableEvent)
	void OnWallsUp();

	UFUNCTION(BlueprintImplementableEvent)
	void OnWallsDown();
	
	void RegisterTileExploration(int XPos, int YPos, EExplorationState ExplorationState);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int TilesExplored;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int TilesCleared;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UTexture2D* ExploredSprite;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UTexture2D* ClearedSprite;
	

	UFUNCTION(BlueprintCallable)
	void InitializeMiniMapArray(TArray<UUserWidget*> TileViewArray);
	
	TArray2D<UMiniMapEntry*> MiniMapArray2D;
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY()
	UGrimGameInstance* GrimGameInstance;
};
