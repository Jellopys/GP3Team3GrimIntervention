// Richard Hill

#pragma once

#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_ToggleMovement.generated.h"

class ABaseEnemy;

UCLASS(Blueprintable)
class UBTTask_ToggleMovement : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTTask_ToggleMovement(FObjectInitializer const& ObjectInitializer);

private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};