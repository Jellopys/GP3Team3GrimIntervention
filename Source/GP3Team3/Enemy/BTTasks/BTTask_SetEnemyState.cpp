// Richard Hill


#include "BTTask_SetEnemyState.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_SetEnemyState::UBTTask_SetEnemyState(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("Set Enemy State");

	// Accept only enums
	// BlackboardKey.AddEnumFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_SetEnemyState, BlackboardKey), StaticEnum<EAIState>() );
}

EBTNodeResult::Type UBTTask_SetEnemyState::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// Get AI Controller & Pawn
	AAIController* AIController = OwnerComp.GetAIOwner();
	UBlackboardComponent* BBComponent = AIController->GetBlackboardComponent();

	BBComponent->SetValueAsEnum(BlackboardKey.SelectedKeyName, (uint8)AIState);

	// Signal the behavior tree component that the task is finished with success
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}
