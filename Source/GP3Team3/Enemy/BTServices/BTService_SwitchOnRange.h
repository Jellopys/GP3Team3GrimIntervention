// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "GP3Team3/Enemy/AIState.h"
#include "BTService_SwitchOnRange.generated.h"

UCLASS()
class UBTService_SwitchOnRange : public UBTService_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTService_SwitchOnRange();
	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:

	UPROPERTY()
	AAIController* AIController;
	UPROPERTY()
	UBlackboardComponent* BBComponent;
	UPROPERTY()
	APawn* AIPawn;
	UPROPERTY()
	APawn* PlayerPawn;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=AI, meta = (AllowPrivateAccess=true))
	float Range = 1000;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	bool SwitchOnOutsideOfRange = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	EAIState AIState;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
