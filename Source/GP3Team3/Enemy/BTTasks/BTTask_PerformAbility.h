// Richard Hill

#pragma once

#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_PerformAbility.generated.h"

class ABaseEnemy;

UCLASS(Blueprintable)
class UBTTask_PerformAbility : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTTask_PerformAbility(FObjectInitializer const& ObjectInitializer);

private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	bool HasMontageFinished(ABaseEnemy* const Enemy);
};