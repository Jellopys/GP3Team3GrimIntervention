// Richard Hill


#include "BTTask_SetCombatStatus.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_SetCombatStatus::UBTTask_SetCombatStatus(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("Set Combat Status");

	// Accept only bools
	BlackboardKey.AddBoolFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_SetCombatStatus, BlackboardKey));
}

EBTNodeResult::Type UBTTask_SetCombatStatus::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// Get AI Controller & Pawn
	AAIController* AIController = OwnerComp.GetAIOwner();
	UBlackboardComponent* BBComponent = AIController->GetBlackboardComponent();

	BBComponent->SetValueAsBool(BlackboardKey.SelectedKeyName, CombatStatus);

	// Signal the behavior tree component that the task is finished with success
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}
