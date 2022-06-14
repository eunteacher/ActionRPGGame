#include "Charactets/CAIController.h"
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
	Sight->SightRadius = 2000.0f;
	Sight->LoseSightRadius = 2000.0f;
	Sight->PeripheralVisionAngleDegrees = 120.0f;
	Sight->SetMaxAge(2.0f);
	
	// Perception 설정
	Perception->ConfigureSense(*Sight);
	Perception->SetDominantSense(*Sight->GetSenseImplementation());

	Sight->DetectionByAffiliation.bDetectEnemies = true;
	Sight->DetectionByAffiliation.bDetectFriendlies = false;
	Sight->DetectionByAffiliation.bDetectNeutrals = false;
}

void ACAIController::BeginPlay()
{
	Super::BeginPlay();

	// TODO : UseBlackboard(BlackboardData, Blackboard) 오류, TObjectptr이 캐스팅이 안되는거 같음.
	UBlackboardComponent* BlackboardComponent = Blackboard;
	if (UseBlackboard(BlackboardData, BlackboardComponent))
	{
		RunBehaviorTree(BehaviorTree);
	}

}

void ACAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	OwnerCharacter = Cast<ACBaseCharacter>(InPawn);
	SetGenericTeamId(OwnerCharacter->GetGenericTeamId());

	// Perception->OnPerceptionUpdated.AddDynamic(this, &ACAIController::OnPerceptionUpdated);

	// UseBlackboard(BehaviorTree->BlackboardAsset, Blackboard);
	// RunBehaviorTree(BehaviorTree);
}

void ACAIController::OnUnPossess()
{
	Super::OnUnPossess();
}
