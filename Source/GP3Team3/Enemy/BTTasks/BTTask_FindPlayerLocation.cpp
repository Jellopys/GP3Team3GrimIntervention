// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindPlayerLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"

UBTTask_FindPlayerLocation::UBTTask_FindPlayerLocation(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("Find Player Location");
}

EBTNodeResult::Type UBTTask_FindPlayerLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	
	// Get AI Controller
	AAIController* AIController = OwnerComp.GetAIOwner();

	// Get Player Location
	APawn* const PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	FVector const PlayerLocation = PlayerPawn->GetActorLocation();
	

	// Set TargetLocation to player location
	AIController->GetBlackboardComponent()->SetValueAsVector(BlackboardKey.SelectedKeyName, PlayerLocation);

	// Signal the behavior tree component that the task is finished with success
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}

FString UBTTask_FindPlayerLocation::GetStaticDescription() const
{
	return FString::Printf(TEXT("Vector: %s"), *BlackboardKey.SelectedKeyName.ToString());
}
