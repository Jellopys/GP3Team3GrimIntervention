// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GenericTeamAgentInterface.h"
#include "GameFramework/PlayerController.h"
#include "GrimPlayerController.generated.h"

UCLASS()
class GP3TEAM3_API AGrimPlayerController : public APlayerController, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	AGrimPlayerController();
	FGenericTeamId TeamID = FGenericTeamId(0);
	virtual FGenericTeamId GetGenericTeamId() const override;

protected:
	virtual void BeginPlay() override;
};
