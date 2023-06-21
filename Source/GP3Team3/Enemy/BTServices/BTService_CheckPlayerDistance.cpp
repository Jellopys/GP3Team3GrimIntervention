// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_CheckPlayerDistance.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

UBTService_CheckPlayerDistance::UBTService_CheckPlayerDistance()
{
	
	bNotifyBecomeRelevant = true;
	NodeName = TEXT("Check Player Distance");
}

void UBTService_CheckPlayerDistance::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);
	// Get AI Controller & Pawn
	AIController = OwnerComp.GetAIOwner();
	BBComponent = AIController->GetBlackboardComponent();
	AIPawn = AIController->GetPawn();
	// Get Player Location
	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
}

void UBTService_CheckPlayerDistance::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	
	BBComponent->SetValueAsFloat(BlackboardKey.SelectedKeyName, AIPawn->GetDistanceTo(PlayerPawn));
}
