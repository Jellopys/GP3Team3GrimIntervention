// Richard Hill

#pragma once

#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_SetCombatStatus.generated.h"

class ABaseEnemy;

UCLASS(Blueprintable)
class UBTTask_SetCombatStatus : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTTask_SetCombatStatus(FObjectInitializer const& ObjectInitializer);

private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	bool CombatStatus;
};