// Fill out your copyright notice in the Description page of Project Settings.


#include "GrimGameInstance.h"

#include "GP3Team3/Player/PlayerStats.h"
#include "GP3Team3/Player/PlayerStats/PlayerStatsDefaultData.h"
#include "GP3Team3/Player/PlayerStats/PlayerStatType.h"
#include "Kismet/GameplayStatics.h"

void UGrimGameInstance::Init()
{
	Super::Init();

	InitializeGameInstance();
}

void UGrimGameInstance::AddCurrency(int AddAmount)
{
	CurrencyBalance += AddAmount;

	SaveGrimGame();
}

int UGrimGameInstance::GetCurrentCurrency()
{
	return CurrencyBalance;
}

void UGrimGameInstance::SpendCurrency(int SpendAmount)
{
	if (CurrencyBalance < SpendAmount)
	{
		return;
	}
	CurrencyBalance -= SpendAmount;

	CurrencySpent+=SpendAmount;

	SaveGrimGame();
}

void UGrimGameInstance::UpgradeStat(const float UpgradeValue, const EPlayerStatType StatType)
{
	switch (StatType)
	{
	case EPlayerStatType::MovementSpeed:
		PlayerStats->MovementSpeed += UpgradeValue;
		break;
	case EPlayerStatType::MaxStamina:
		PlayerStats->MaxStamina += UpgradeValue;
		break;
	case EPlayerStatType::StaminaGainMultiplier:
		PlayerStats->StaminaGainMultiplier += UpgradeValue;
		break;
	case EPlayerStatType::StaminaRegainTime:
		PlayerStats->StaminaRegainTime += UpgradeValue;
		break;
	case EPlayerStatType::DashPower:
		PlayerStats->DashPower += UpgradeValue;
		break;
	case EPlayerStatType::MaxHealth:
		PlayerStats->MaxHealth += UpgradeValue;
		break;
	case EPlayerStatType::FirstComboDamage:
		PlayerStats->FirstComboDamage += UpgradeValue;
		break;
	case EPlayerStatType::SecondComboDamage:
		PlayerStats->SecondComboDamage += UpgradeValue;
		break;
	case EPlayerStatType::ThirdComboDamage:
		PlayerStats->ThirdComboDamage += UpgradeValue;
		break;
	case EPlayerStatType::AttackSpeed:
		PlayerStats->AttackSpeed += UpgradeValue;
		break;
	case EPlayerStatType::DashStaminaCost:
		PlayerStats->DashStaminaCost += UpgradeValue;
		break;
	case EPlayerStatType::BaseDamageMultiplier:
		PlayerStats->BaseDamageMultiplier += UpgradeValue;
		break;
	case EPlayerStatType::AttackRangeMultiplier:
		PlayerStats->AttackRangeMultiplier += UpgradeValue;
		break;
	case EPlayerStatType::ScytheTossStaminaCost:
		PlayerStats->ScytheTossStaminaCost += UpgradeValue;
		break;
	case EPlayerStatType::ScytheTossDamage:
		PlayerStats->ScytheTossDamage += UpgradeValue;
		break;
	case EPlayerStatType::DashDamage:
		PlayerStats->DashDamage += UpgradeValue;
		break;
	case EPlayerStatType::CritChance:
		PlayerStats->CritChance += UpgradeValue;
		break;
	case EPlayerStatType::CritDamage:
		PlayerStats->CritDamage += UpgradeValue;
		break;
	
	default:
		break;
	}
}

void UGrimGameInstance::SetDefaultPlayerStats()
{
	PlayerStats = new FPlayerStats;

	if (PlayerStatsDefaultData)
	{
		// Movement & Dash
		PlayerStats->MovementSpeed = PlayerStatsDefaultData->MovementSpeed + (SpeedUpgrades * (PlayerStatsDefaultData->MovementSpeed*0.08f));
		PlayerStats->DashPower = PlayerStatsDefaultData->DashPower + (DashDistanceUpgrades * (PlayerStatsDefaultData->DashPower*0.1f));
		PlayerStats->DashCooldown = PlayerStatsDefaultData->DashCooldown;
		PlayerStats->DashDuration = PlayerStatsDefaultData->DashDuration;

		//Dash Combat
		PlayerStats->DashDamage = PlayerStatsDefaultData->DashDamage;
		
		// Health
		PlayerStats->MaxHealth = PlayerStatsDefaultData->MaxHealth + (MaxHealthUpgrades * 10);

		// Stamina
		PlayerStats->MaxStamina = PlayerStatsDefaultData->MaxStamina + (MaxStaminaUpgrades * (PlayerStatsDefaultData->MaxStamina*0.2f));
		PlayerStats->CurrentStamina = PlayerStatsDefaultData->CurrentStamina;
		PlayerStats->StaminaGainMultiplier = PlayerStatsDefaultData->StaminaGainMultiplier;
		PlayerStats->StaminaRegainTime = PlayerStatsDefaultData->StaminaRegainTime;
		PlayerStats->DashStaminaCost = PlayerStatsDefaultData->DashStaminaCost;
		PlayerStats->ScytheTossStaminaCost = PlayerStatsDefaultData->ScytheTossStaminaCost;
		
		// Combat
		PlayerStats->FirstComboDamage = PlayerStatsDefaultData->FirstComboDamage;
		PlayerStats->SecondComboDamage = PlayerStatsDefaultData->SecondComboDamage;
		PlayerStats->ThirdComboDamage = PlayerStatsDefaultData->ThirdComboDamage;
		PlayerStats->AttackSpeed = PlayerStatsDefaultData->AttackSpeed;
		PlayerStats->BaseDamageMultiplier = PlayerStatsDefaultData->BaseDamageMultiplier + (DamageUpgrades * .1f);
		PlayerStats->AttackRangeMultiplier = PlayerStatsDefaultData->AttackRangeMultiplier;
		PlayerStats->ScytheTossDamage = PlayerStatsDefaultData->ScytheTossDamage;

		//Crit
		PlayerStats->CritChance = PlayerStatsDefaultData->CritChance + (LuckUpgrades * .02f);
		PlayerStats->CritDamage = PlayerStatsDefaultData->CritDamage;
	}
}

FPlayerStats* UGrimGameInstance::GetPlayerStats()
{
	return PlayerStats;
}

void UGrimGameInstance::InitializeGameInstance()
{
	LoadGrimGame();
	SetDefaultPlayerStats();
}

float UGrimGameInstance::GetStat(EPlayerStatType StatType)
{
	switch (StatType)
	{
	case EPlayerStatType::MovementSpeed:
		return PlayerStats->MovementSpeed;
	case EPlayerStatType::MaxStamina:
		return PlayerStats->MaxStamina;
	case EPlayerStatType::StaminaGainMultiplier:
		return PlayerStats->StaminaGainMultiplier;
	case EPlayerStatType::StaminaRegainTime:
		return PlayerStats->StaminaRegainTime;
	case EPlayerStatType::DashPower:
		return PlayerStats->DashPower;
	case EPlayerStatType::MaxHealth:
		return PlayerStats->MaxHealth;
	case EPlayerStatType::FirstComboDamage:
		return PlayerStats->FirstComboDamage;
	case EPlayerStatType::SecondComboDamage:
		return PlayerStats->SecondComboDamage;
	case EPlayerStatType::ThirdComboDamage:
		return PlayerStats->ThirdComboDamage;
	case EPlayerStatType::AttackSpeed:
		return PlayerStats->AttackSpeed;
	case EPlayerStatType::DashStaminaCost:
		return PlayerStats->DashStaminaCost;
	case EPlayerStatType::BaseDamageMultiplier:
		return PlayerStats->BaseDamageMultiplier;
	case EPlayerStatType::AttackRangeMultiplier:
		return PlayerStats->AttackRangeMultiplier;
	case EPlayerStatType::ScytheTossStaminaCost:
		return PlayerStats->ScytheTossStaminaCost;
	case EPlayerStatType::ScytheTossDamage:
		return PlayerStats->ScytheTossDamage;
	case EPlayerStatType::DashDamage:
		return PlayerStats->DashDamage;
	case EPlayerStatType::CritChance:
		return PlayerStats->CritChance;
	case EPlayerStatType::CritDamage:
		return PlayerStats->CritDamage;
	
	default:
		return 0;
	}
}

void UGrimGameInstance::SetPlayerRef(APlayerCharacter* Player)
{
	PlayerRef = Player;
}

APlayerCharacter* UGrimGameInstance::GetPlayerRef()
{
	return PlayerRef;
}

void UGrimGameInstance::SaveGrimGame()
{
		SaveFileInstance->CurrencyBalance = CurrencyBalance;
		SaveFileInstance->CurrencySpent = CurrencySpent;

		SaveFileInstance->MetaMaxHealthUpgrades = MaxHealthUpgrades;
		SaveFileInstance->MetaMaxStaminaUpgrades = MaxStaminaUpgrades;
		SaveFileInstance->MetaSpeedUpgrades = SpeedUpgrades;
		SaveFileInstance->MetaDashDistanceUpgrades = DashDistanceUpgrades;
		SaveFileInstance->MetaLuckUpgrades = LuckUpgrades;
		SaveFileInstance->MetaDamageUpgrades = DamageUpgrades;
		
		UGameplayStatics::SaveGameToSlot(SaveFileInstance, TEXT("MetaSave"), 0);
}

void UGrimGameInstance::LoadGrimGame()
{
	if(UGameplayStatics::DoesSaveGameExist("MetaSave", 0))
	{
		SaveFileInstance = Cast<USaveFile>(UGameplayStatics::LoadGameFromSlot("MetaSave", 0));
	}
	else
	{
		SaveFileInstance = Cast<USaveFile>(UGameplayStatics::CreateSaveGameObject(USaveFile::StaticClass()));
	}

	CurrencyBalance = SaveFileInstance->CurrencyBalance;
	CurrencySpent = SaveFileInstance->CurrencySpent;

	MaxHealthUpgrades = SaveFileInstance->MetaMaxHealthUpgrades;
	MaxStaminaUpgrades = SaveFileInstance->MetaMaxStaminaUpgrades;
	SpeedUpgrades = SaveFileInstance->MetaSpeedUpgrades;
	DashDistanceUpgrades = SaveFileInstance->MetaDashDistanceUpgrades;
	LuckUpgrades = SaveFileInstance->MetaLuckUpgrades;
	DamageUpgrades = SaveFileInstance->MetaDamageUpgrades;
}

int UGrimGameInstance::GetMetaUpgradeTimesBought(const EMetaUpgradeType UpgradeType) const
{
	switch (UpgradeType)
	{
	case EMetaUpgradeType::MaxHealth:
		return MaxHealthUpgrades;
	case EMetaUpgradeType::MaxStamina:
		return MaxStaminaUpgrades;
	case EMetaUpgradeType::DashDistance:
		return DashDistanceUpgrades;
	case EMetaUpgradeType::Speed:
		return SpeedUpgrades;
	case EMetaUpgradeType::Luck:
		return LuckUpgrades;
	case EMetaUpgradeType::Damage:
		return DamageUpgrades;
	default:
		return 0;
	}
}

void UGrimGameInstance::UpgradeMetaStat(EMetaUpgradeType UpgradeType)
{
	switch (UpgradeType)
	{
	case EMetaUpgradeType::MaxHealth:
		if(MaxHealthUpgrades < 5)
		{
			MaxHealthUpgrades++;
		}
		break;
	case EMetaUpgradeType::MaxStamina:
		if(MaxStaminaUpgrades < 5)
		{
			MaxStaminaUpgrades++;
		}
		break;
	case EMetaUpgradeType::DashDistance:
		if(DashDistanceUpgrades < 5)
		{
			DashDistanceUpgrades++;
		}
		break;
	case EMetaUpgradeType::Speed:
		if(SpeedUpgrades < 5)
		{
			SpeedUpgrades++;
		}
		break;
	case EMetaUpgradeType::Luck:
		if(LuckUpgrades < 5)
		{
			LuckUpgrades++;
		}
		break;
	case EMetaUpgradeType::Damage:
		if(DamageUpgrades < 5)
		{
			DamageUpgrades++;
		}
		break;
	default:
		return;
	}

	SaveGrimGame();
}

void UGrimGameInstance::RespecUpgrades()
{
	if (!SaveFileInstance){ return;}
	
	MaxHealthUpgrades = 0;
	MaxStaminaUpgrades = 0;
	DashDistanceUpgrades = 0;
	SpeedUpgrades = 0;
	LuckUpgrades = 0;
	DamageUpgrades = 0;

	AddCurrency(CurrencySpent);
	CurrencySpent = 0;

	SaveGrimGame();
}
