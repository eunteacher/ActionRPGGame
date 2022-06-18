#include "Notifies/CAnimNotify_Dead.h"
#include "Characters/CBaseCharacter.h"

FString UCAnimNotify_Dead::GetNotifyName_Implementation() const
{
	return "Dead";
}

void UCAnimNotify_Dead::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (IsValid(MeshComp->GetOwner<ACBaseCharacter>()))
	{
		MeshComp->GetOwner<ACBaseCharacter>()->OnDead();
	}
}
