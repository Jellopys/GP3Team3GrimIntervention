// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerupBase.h"

#include "Blueprint/UserWidget.h"
#include "GP3Team3/UI/UPowerupCollectWidget.h"
#include "Kismet/GameplayStatics.h"

void UPowerupBase::RegisterPowerUp(APlayerCharacter* PlayerC, AGrimGameMode* GameM, UGrimGameInstance* GameI)
{
	PlayerCharacter = PlayerC;
	GameMode = GameM;
	GameInstance = GameI;

	OnPowerUpGotten();
}
