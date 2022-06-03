#include "Notifies/CAnimNotify_Idle.h"
#include "Charactets/CBaseCharacter.h"
#include "Components/CStateComponent.h"
#include "Types/CEnumTypes.h"

FString UCAnimNotify_Idle::GetNotifyName_Implementation() const
{
	return "Idle_Walk_Run";
}

void UCAnimNotify_Idle::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	// 캐릭터의 State 컴포넌트의 SetState()를 호출해 Idle_Walk_Run 상태로 만든다.
	if (IsValid(MeshComp->GetOwner<ACBaseCharacter>()))
	{
		UCStateComponent* state = Cast<UCStateComponent>(MeshComp->GetOwner<ACBaseCharacter>()->GetComponentByClass(UCStateComponent::StaticClass()));
		state->SetStateType(EStateType::Idle_Walk_Run);
	}
}
