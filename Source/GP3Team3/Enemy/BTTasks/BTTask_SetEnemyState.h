// Richard Hill

#pragma once

#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "GP3Team3/Enemy/AIState.h"
#include "BTTask_SetEnemyState.generated.h"

class ABaseEnemy;

UCLASS(Blueprintable)
class UBTTask_SetEnemyState : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTTask_SetEnemyState(FObjectInitializer const& ObjectInitializer);

private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	EAIState AIState;
};

