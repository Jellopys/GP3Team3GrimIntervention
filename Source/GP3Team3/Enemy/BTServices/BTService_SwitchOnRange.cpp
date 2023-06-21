// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_SwitchOnRange.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

UBTService_SwitchOnRange::UBTService_SwitchOnRange()
{
	bNotifyBecomeRelevant = true;
	NodeName = TEXT("Switch On Player Distance");
}

void UBTService_SwitchOnRange::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{	
	// Get AI Controller & Pawn
	AIController = OwnerComp.GetAIOwner();
	BBComponent = AIController->GetBlackboardComponent();
	AIPawn = AIController->GetPawn();
	// Get Player Location
	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	Super::OnBecomeRelevant(OwnerComp, NodeMemory);
}

void UBTService_SwitchOnRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	if (!AIPawn) return;
	if (!PlayerPawn) return;
	// Set State value based on the distance to the player
	if (SwitchOnOutsideOfRange) // if bool is set to true, Change state if player is OUTSIDE of the range
	{
		if (AIPawn->GetDistanceTo(PlayerPawn) >= Range)
		{
			BBComponent->SetValueAsEnum(BlackboardKey.SelectedKeyName, (uint8)AIState);
		}
	}
	else // if bool is set to false, Change state if player is inside of the range
	{
		if (AIPawn->GetDistanceTo(PlayerPawn) <= Range)
		{
			BBComponent->SetValueAsEnum(BlackboardKey.SelectedKeyName, (uint8)AIState);
		}
	}
}
