#include "BehaviorTree/CBTService_DistanceToTarget.h"
#include "ActionRPGGame.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/CAIController.h"
#include "Characters/CBaseCharacter.h"

UCBTService_DistanceToTarget::UCBTService_DistanceToTarget()
{
	NodeName = "BTService_DistanceToTarget";
}

void UCBTService_DistanceToTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);


	ACAIController* controller = OwnerComp.GetOwner<ACAIController>();
	if(IsValid(controller))
	{

		ACBaseCharacter* ownerCharacter = controller->GetPawn<ACBaseCharacter>();
		if(IsValid(ownerCharacter) && ownerCharacter->GetAlive() && IsValid(controller->GetTarget()))
		{
			if(controller->GetTarget()->GetStatusType() == EStatusType::Player)
			{
				controller->SetFindTarget(true);

				FVector v1 = ownerCharacter->GetActorLocation();
				FVector v2 = controller->GetTarget()->GetActorLocation();
				controller->SetDistanceToTarget(UKismetMathLibrary::Vector_Distance(v1, v2));
			}
			else
			{
				controller->SetFindTarget(false);
			}
		} // IsValid ownerCharacter, GetAlive, controller->GetTarget
	} 

}
