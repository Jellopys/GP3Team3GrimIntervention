// Fill out your copyright notice in the Description page of Project Settings.


#include "GrimPlayerController.h"

#include "Framework/Application/NavigationConfig.h"

AGrimPlayerController::AGrimPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
}

FGenericTeamId AGrimPlayerController::GetGenericTeamId() const
{
	return TeamID;
}

void AGrimPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	TSharedRef<FNavigationConfig> Navigation = MakeShared<FNavigationConfig>();
	Navigation->bKeyNavigation = false;
	Navigation->bTabNavigation = false;
	Navigation->bAnalogNavigation = false;
	FSlateApplication::Get().SetNavigationConfig(Navigation);
}

