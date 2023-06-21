// Fill out your copyright notice in the Description page of Project Settings.


#include "MovementStatics.h"
#include "GameFramework/Actor.h"
#include "Components/SceneComponent.h"

FMovementStatics::FMovementStatics(AActor* InActor)
{
	StartLocation = InActor->GetActorLocation();
}

FMovementStatics::FMovementStatics(USceneComponent* InSceneComponent)
{
	StartLocation = InSceneComponent->GetComponentLocation();
}

void FMovementStatics::AddDelta(const FVector& InDelta)
{
	MovementDelta += InDelta;
}
