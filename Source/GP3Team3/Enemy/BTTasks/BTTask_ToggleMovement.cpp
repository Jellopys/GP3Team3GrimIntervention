// Richard Hill


#include "BTTask_ToggleMovement.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GP3Team3/Enemy/BaseEnemy.h"

UBTTask_ToggleMovement::UBTTask_ToggleMovement(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("Stop Movement");

	// Accept only bools
	// BlackboardKey.AddBoolFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_ToggleMovement, BlackboardKey));
}

EBTNodeResult::Type UBTTask_ToggleMovement::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// Get AI Controller & Pawn
	AAIController* AIController = OwnerComp.GetAIOwner();
	
	AIController->StopMovement();

	// Signal the behavior tree component that the task is finished with success
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}
