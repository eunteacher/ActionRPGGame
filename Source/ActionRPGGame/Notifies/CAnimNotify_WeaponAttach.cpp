#include "Notifies/CAnimNotify_WeaponAttach.h"
#include "Charactets/CBaseCharacter.h"

FString UCAnimNotify_WeaponAttach::GetNotifyName_Implementation() const
{
	return "WeaponAttach";
}

void UCAnimNotify_WeaponAttach::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (IsValid(MeshComp->GetOwner<ACBaseCharacter>()))
	{
		
	}
}
