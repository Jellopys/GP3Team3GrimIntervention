// Richard Hill

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "GrimAIController.generated.h"

struct FAIStimulus;
class UAISenseConfig_Hearing;
class UAISenseConfig_Sight;
class UBehaviorTreeComponent;
class UBehaviorTree;
class UBlackboardComponent;
class UAIPerceptionComponent;

UCLASS()
class AGrimAIController : public AAIController
{
	GENERATED_BODY()

public:
	AGrimAIController();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = AI)
	UBehaviorTree* BehaviorTree;
	UPROPERTY(EditAnywhere, Category = AI)
	UAIPerceptionComponent* AIPerceptionComponent;
	
	UFUNCTION()
	UBlackboardComponent* GetBlackboard();
	void SetBehaviorTree(UBehaviorTree* BehaveTree);

protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI, meta=(AllowPrivateAccess = true))
	UBehaviorTreeComponent* BehaviorTreeComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI, meta=(AllowPrivateAccess = true))
	UBlackboardComponent* BlackboardComponent;

	UPROPERTY(VisibleAnywhere, Category = AI, meta=(AllowPrivateAccess = true))
	UAISenseConfig_Sight* AISenseConfigSight = nullptr;
	UPROPERTY(VisibleAnywhere, Category = AI, meta=(AllowPrivateAccess = true))
	UAISenseConfig_Hearing* AISenseConfigHearing = nullptr;

	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;

	UFUNCTION()
	void OnTargetPerceptionUpdated_Delegate(AActor* Actor, FAIStimulus Stimulus);
	UFUNCTION()
	void OnTargetDetected(AActor* Actor, FAIStimulus Stimulus);
};
