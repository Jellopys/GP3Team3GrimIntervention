// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "USaveFile.h"
#include "Engine/GameInstance.h"
#include "GP3Team3/UI/MetaItem.h"
#include "GP3Team3/UI/UMetaShopEntry.h"
#include "GrimGameInstance.generated.h"

class APlayerCharacter;
enum class EPlayerStatType : uint8;
class UPlayerStatsDefaultData;
struct FPlayerStats;

UCLASS()
class UGrimGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	
	virtual void Init() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerStats)
	UPlayerStatsDefaultData* PlayerStatsDefaultData;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	APlayerCharacter* PlayerRef;
	
	FPlayerStats* PlayerStats;

	UFUNCTION(BlueprintCallable)
	void AddCurrency(int AddAmount);

	UFUNCTION(BlueprintCallable)
	int GetCurrentCurrency();

	UFUNCTION(BlueprintCallable)
	void SpendCurrency(int SpendAmount);

	UFUNCTION(BlueprintCallable)
	void UpgradeStat(const float UpgradeValue, const EPlayerStatType StatType);

	UFUNCTION(BlueprintCallable)
	void SetDefaultPlayerStats();
	
	FPlayerStats* GetPlayerStats();


	UFUNCTION(BlueprintCallable)
	void InitializeGameInstance();

	UFUNCTION(BlueprintCallable)
	float GetStat(EPlayerStatType StatType);

	UFUNCTION()
	void SetPlayerRef(APlayerCharacter* Player);

	UFUNCTION(BlueprintCallable)
	APlayerCharacter* GetPlayerRef();
	
	//Game Save
	UPROPERTY()
	USaveFile* SaveFileInstance;

	void SaveGrimGame();
	void LoadGrimGame();

	//Meta

	int GetMetaUpgradeTimesBought(EMetaUpgradeType UpgradeType) const;
	void UpgradeMetaStat(EMetaUpgradeType UpgradeType);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int CurrencyBalance;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int CurrencySpent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int MaxHealthUpgrades;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int SpeedUpgrades;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int MaxStaminaUpgrades;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int DashDistanceUpgrades;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int LuckUpgrades;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int DamageUpgrades;
	
	UFUNCTION(BlueprintCallable)
	void RespecUpgrades();
};
