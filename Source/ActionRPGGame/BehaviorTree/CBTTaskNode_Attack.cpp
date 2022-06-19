#include "BehaviorTree/CBTTaskNode_Attack.h"
#include "Characters/CAIController.h"
#include "Characters/CBaseCharacter.h"
#include "Weapon/CWeapon.h"

UCBTTaskNode_Attack::UCBTTaskNode_Attack()
{
	NodeName = "BTTaskNode_Attack";
}

EBTNodeResult::Type UCBTTaskNode_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if(IsValid(OwnerComp.GetOwner<ACAIController>()))
	{
		ACBaseCharacter* ownerCharacter = OwnerComp.GetOwner<ACAIController>()->GetPawn<ACBaseCharacter>();
		if(IsValid(ownerCharacter))
		{
			if(ownerCharacter->GetEquipWeaponDataMaps().Contains(ownerCharacter->GetWeaponType()))
			{
				ownerCharacter->GetEquipWeaponDataMaps().Find(ownerCharacter->GetWeaponType())->Weapon->OnAttack();
				return EBTNodeResult::Succeeded;
			}
		}
	}
	
	return EBTNodeResult::Failed;
}
