#include "BehaviorTree/CBTTaskNode_Patrol.h"
#include "ActionRPGGame.h"
#include "Charactets/CAIController.h"
#include "Charactets/CBaseCharacter.h"
#include "Patrols/CPatrolComponent.h"

UCBTTaskNode_Patrol::UCBTTaskNode_Patrol()
{
	bNotifyTick = true;
	NodeName = "BTTaskNode_Patrol";
}

EBTNodeResult::Type UCBTTaskNode_Patrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return EBTNodeResult::InProgress;
}

void UCBTTaskNode_Patrol::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	// 컨트롤러를 가져온다.
	ACAIController* controller = Cast<ACAIController>(OwnerComp.GetOwner());
	
	if(IsValid(controller))
	{
		// 가져온 컨트롤러로 OwnerCharcter를 가져온다.
		ACBaseCharacter* OwnerCharacter = Cast<ACBaseCharacter>(controller->GetPawn());
		if(IsValid(OwnerCharacter))
		{
			// OwnerCharacter의 Patrol 컴포넌트를 가져온다.
			UCPatrolComponent* patrol = Cast<UCPatrolComponent>(OwnerCharacter->GetComponentByClass(UCPatrolComponent::StaticClass()));
			if(patrol->CanPatorl() && IsValid(patrol))
			{
				// Patrol 컴포넌트에서 Spline Point 위치와 Radius를 가져와 매개변수를 입력한다.
				EPathFollowingRequestResult::Type type = controller->MoveToLocation(patrol->GetPointLocation(), patrol->GetRadius());
				
				if(type == EPathFollowingRequestResult::Failed)
				{
					FinishLatentTask(OwnerComp, EBTNodeResult::InProgress);
				}

				if(type == EPathFollowingRequestResult::AlreadyAtGoal)
				{
					// Spline Point를 Update하여 다음 Path를 지정한다.
					patrol->UpdateNextPath();
					FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
				}			
			}
		} // if(IsValid(OwnerCharacter))
	} // if(IsValid(controller))
}
