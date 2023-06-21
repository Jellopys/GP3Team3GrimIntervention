// Richard Hill


#include "BTTask_SetEnemyStateInRange.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

UBTTask_SetEnemyStateInRange::UBTTask_SetEnemyStateInRange(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("Set Enemy State In Range");
}

EBTNodeResult::Type UBTTask_SetEnemyStateInRange::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// Get AI Controller & Pawn
	AAIController* AIController = OwnerComp.GetAIOwner();
	UBlackboardComponent* BBComponent = AIController->GetBlackboardComponent();

	// Get AI Controller & Pawn
	APawn* AIPawn = AIController->GetPawn();
	// Get Player Location
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	if (AIPawn->GetDistanceTo(PlayerPawn) >= Range)
	{
		BBComponent->SetValueAsEnum(BlackboardKey.SelectedKeyName, (uint8)AboveRangeAIState);
	}
	else
	{
		BBComponent->SetValueAsEnum(BlackboardKey.SelectedKeyName, (uint8)BelowRangeAIState);
	}

	// Signal the behavior tree component that the task is finished with success
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}
