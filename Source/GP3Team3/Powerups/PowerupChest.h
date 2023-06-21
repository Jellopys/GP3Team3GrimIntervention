// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Widget.h"
#include "GameFramework/Actor.h"
#include "GP3Team3/GameEssentials/GrimGameMode.h"
#include "GP3Team3/Player/PlayerStats/PlayerStatType.h"
#include "PowerupChest.generated.h"

class UOpenChestWidget;

UCLASS()
class GP3TEAM3_API APowerupChest : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APowerupChest();

	UFUNCTION(BlueprintCallable, Category = "PowerUp Chest Functions")
	void OpenChest();

	UOpenChestWidget* OpenChestWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UWidget* TreasureIconRef;
	
	void TakePowerup();
	void TakePowerup2();

	UFUNCTION(BlueprintImplementableEvent)
	void OnChestOpen();

	UFUNCTION(BlueprintImplementableEvent)
	void OnChestClose();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	TSubclassOf<UPowerupBase> item_class;
	UPROPERTY()
	TSubclassOf<UPowerupBase> item_class2;

	UPROPERTY()
	AGrimGameMode* GameModeRef;
	UPROPERTY()
	UGrimGameInstance* GameInstanceRef;
	UPROPERTY()
	APlayerCharacter* PlayerRef;

	UPROPERTY()
	UPowerupBase* SelectedPowerup;
	UPROPERTY()
	UPowerupBase* SelectedPowerup2;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UOpenChestWidget> ChestOpenWidgetClass;

	bool HasOpened;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
