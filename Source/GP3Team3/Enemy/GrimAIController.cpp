// Richard Hill


#include "GrimAIController.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GP3Team3/Player/PlayerCharacter.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AISenseConfig_Sight.h"

AGrimAIController::AGrimAIController()
{
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("Behavior Tree Component"));
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard Component"));

	// AI Perception
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component"));
	
	AISenseConfigSight = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SenseSight"));
	AISenseConfigSight->DetectionByAffiliation.bDetectEnemies = true;
	AISenseConfigSight->DetectionByAffiliation.bDetectFriendlies = true;
	AISenseConfigSight->DetectionByAffiliation.bDetectEnemies = true;
	
	AISenseConfigHearing = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("SenseHearing"));
	AISenseConfigHearing->DetectionByAffiliation.bDetectEnemies = true;
	AISenseConfigHearing->DetectionByAffiliation.bDetectFriendlies = true;
	AISenseConfigHearing->DetectionByAffiliation.bDetectEnemies = true;

	AIPerceptionComponent->ConfigureSense(*AISenseConfigSight);
	AIPerceptionComponent->ConfigureSense(*AISenseConfigHearing);
	AIPerceptionComponent->SetDominantSense(UAISenseConfig_Sight::StaticClass());
	// Add Team ID for detection
	AAIController::SetGenericTeamId(FGenericTeamId(1));
}

void AGrimAIController::SetBehaviorTree(UBehaviorTree* BehaveTree)
{
	if (IsValid(BehaveTree))
	{
		RunBehaviorTree(BehaveTree);
		BehaviorTreeComponent->StartTree(*BehaveTree);
	}
}

UBlackboardComponent* AGrimAIController::GetBlackboard()
{
	return BlackboardComponent;
}

void AGrimAIController::BeginPlay()
{
	Super::BeginPlay();
	
	// if (IsValid(BehaviorTree))
	// {
	// 	RunBehaviorTree(BehaviorTree);
	// 	BehaviorTreeComponent->StartTree(*BehaviorTree);
	// }

	AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &ThisClass::OnTargetPerceptionUpdated_Delegate);
}

void AGrimAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (IsValid(Blackboard) && IsValid(BehaviorTree))
	{
		Blackboard->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
	}
}

ETeamAttitude::Type AGrimAIController::GetTeamAttitudeTowards(const AActor& Other) const
{
	if (APawn const* OtherPawn = Cast<APawn>(&Other))
	{
		if (auto const TeamAgent = Cast<IGenericTeamAgentInterface>(OtherPawn->GetController()))
		{
			if (TeamAgent->GetGenericTeamId() == FGenericTeamId(1))
			{
				return ETeamAttitude::Friendly;
			}
			else
			{
				return ETeamAttitude::Hostile;
			}
		}
	}
	return ETeamAttitude::Neutral;
}

void AGrimAIController::OnTargetPerceptionUpdated_Delegate(AActor* Actor, FAIStimulus Stimulus)
{
	switch (Stimulus.Type)
	{
		case 0: // Sight
			OnTargetDetected(Actor, Stimulus);
		case 1:
			// OnTargetDetected(Actor, Stimulus);
		default:
			return;
	}
}

void AGrimAIController::OnTargetDetected(AActor* Actor, FAIStimulus Stimulus)
{
	if (auto const PlayerPawn = Cast<APlayerCharacter>(Actor))
	{
		Blackboard->SetValueAsBool(TEXT("CanSeePlayer"), Stimulus.WasSuccessfullySensed());
	}
}

