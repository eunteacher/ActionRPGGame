#include "Notifies/CAnimNotify_Idle.h"
#include "Charactets/CBaseCharacter.h"
#include "Types/CEnumTypes.h"

FString UCAnimNotify_Idle::GetNotifyName_Implementation() const
{
	return "Idle_Walk_Run";
}

void UCAnimNotify_Idle::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	// ACBaseChracter에서 SetState()를 호출해 Idle_Walk_Run 상태로 만든다.
	if (IsValid(MeshComp->GetOwner<ACBaseCharacter>()))
	{
		MeshComp->GetOwner<ACBaseCharacter>()->SetState(EStateType::Idle_Walk_Run);
	}
}
