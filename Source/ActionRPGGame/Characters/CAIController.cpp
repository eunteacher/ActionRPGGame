#include "Characters/CAIController.h"
#include "CBaseCharacter.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BlackboardData.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

ACAIController::ACAIController()
{
	// BlackboardData'/Game/Enemy/Blueprints/BB_Enemy.BB_Enemy'
	const ConstructorHelpers::FObjectFinder<UBlackboardData> blackboardDataAsset(TEXT("BlackboardData'/Game/Enemy/Blueprints/BB_Enemy.BB_Enemy'"));
	if(blackboardDataAsset.Succeeded())
	{
		BlackboardData = blackboardDataAsset.Object;
	}

	// BehaviorTree'/Game/Enemy/Blueprints/Grunting/BT_Grunting.BT_Grunting'
	const ConstructorHelpers::FObjectFinder<UBehaviorTree> behaviorTreeAsset(TEXT("BehaviorTree'/Game/Enemy/Blueprints/Grunting/BT_Grunting.BT_Grunting'"));
	if (behaviorTreeAsset.Succeeded())
	{
		BehaviorTree = behaviorTreeAsset.Object;
	}
	
	// AIPerception 컴포넌트 생성
	Perception = CreateDefaultSubobject<UAIPerceptionComponent>("Perception");

	// AISenseConfig_Sight 생성 및 초기화
	Sight = CreateDefaultSubobject<UAISenseConfig_Sight>("Sight");
	Sight->SightRadius = 3000.0f;
	Sight->LoseSightRadius = 3500.0f;
	Sight->PeripheralVisionAngleDegrees = 90.0f;
	Sight->SetMaxAge(0.0f);
	
	// Perception 설정
	Perception->ConfigureSense(*Sight);
	Perception->SetDominantSense(*Sight->GetSenseImplementation());

	Sight->DetectionByAffiliation.bDetectEnemies = true;
	Sight->DetectionByAffiliation.bDetectFriendlies = false;
	Sight->DetectionByAffiliation.bDetectNeutrals = false;
}

ACBaseCharacter* ACAIController::GetTarget()
{
	FName keyName = "Target";
	return Cast<ACBaseCharacter>(Blackboard->GetValueAsObject(keyName));
}

void ACAIController::SetDistanceToTarget(float InDistance)
{
	FName keyName = "DistanceToTarget";
	Blackboard->SetValueAsFloat(keyName, InDistance);
}

void ACAIController::SetFindTarget(bool InFindTarget)
{
	FName keyName = "FindTarget";
	Blackboard->SetValueAsBool(keyName, InFindTarget);
}

void ACAIController::BeginPlay()
{
	Super::BeginPlay();

	// TODO : UseBlackboard(BlackboardData, Blackboard) 오류, TObjectptr이 캐스팅이 안되는거 같음.
	UBlackboardComponent* blackboardComponent = Blackboard;
	if (UseBlackboard(BlackboardData, blackboardComponent))
	{
		RunBehaviorTree(BehaviorTree);
	}

}

void ACAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	OwnerCharacter = Cast<ACBaseCharacter>(InPawn);
	SetGenericTeamId(OwnerCharacter->GetGenericTeamId());

	Perception->OnTargetPerceptionUpdated.AddDynamic(this, &ACAIController::OnTargetPerceptionUpdated);
}

void ACAIController::OnUnPossess()
{
	Super::OnUnPossess();
}

void ACAIController::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if(Cast<ACBaseCharacter>(Actor)->GetStatusType() == EStatusType::Player && Stimulus.WasSuccessfullySensed())
	{
		Blackboard->SetValueAsObject("Target", Cast<ACBaseCharacter>(Actor));
	}
	else
	{
		Blackboard->SetValueAsObject("Target", nullptr);
	}
}
