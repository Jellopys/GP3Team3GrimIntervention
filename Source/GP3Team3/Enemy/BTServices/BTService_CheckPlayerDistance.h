// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "GP3Team3/Enemy/AIState.h"
#include "BTService_CheckPlayerDistance.generated.h"

UCLASS()
class UBTService_CheckPlayerDistance : public UBTService_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTService_CheckPlayerDistance();
	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY()
	AAIController* AIController;
	UPROPERTY()
	UBlackboardComponent* BBComponent;
	UPROPERTY()
	APawn* AIPawn;
	UPROPERTY()
	APawn* PlayerPawn;
};
