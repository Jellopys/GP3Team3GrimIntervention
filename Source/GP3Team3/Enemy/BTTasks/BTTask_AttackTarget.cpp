// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_AttackTarget.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GP3Team3/Enemy/BaseEnemy.h"

UBTTask_AttackTarget::UBTTask_AttackTarget(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("Attack Target");
}

EBTNodeResult::Type UBTTask_AttackTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// Get AI Controller & Pawn
	AAIController* AIController = OwnerComp.GetAIOwner();
	UBlackboardComponent* BBComponent = AIController->GetBlackboardComponent();
	ABaseEnemy* AICharacter = Cast<ABaseEnemy>(AIController->GetCharacter());

	if (IsValid(AICharacter))
	{
		BBComponent->SetValueAsFloat(BlackboardKey.SelectedKeyName, AICharacter->GetAttackTime());
		AICharacter->PerformAttack();
	}

	// Signal the behavior tree component that the task is finished with success
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}

bool UBTTask_AttackTarget::HasMontageFinished(ABaseEnemy* const Enemy)
{
	return false;
}
