// Richard Hill

#pragma once

#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "GP3Team3/Enemy/AIState.h"
#include "BTTask_SetEnemyStateInRange.generated.h"

class ABaseEnemy;

UCLASS(Blueprintable)
class UBTTask_SetEnemyStateInRange : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTTask_SetEnemyStateInRange(FObjectInitializer const& ObjectInitializer);

private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	EAIState BelowRangeAIState;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	EAIState AboveRangeAIState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	float Range = 200;
};

