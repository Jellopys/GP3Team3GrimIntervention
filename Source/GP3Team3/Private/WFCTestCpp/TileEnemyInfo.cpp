// Fill out your copyright notice in the Description page of Project Settings.


#include "GP3Team3/Public/WFCTestCpp/TileEnemyInfo.h"

// Sets default values for this component's properties
UTileEnemyInfo::UTileEnemyInfo()
{
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UTileEnemyInfo::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void UTileEnemyInfo::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

