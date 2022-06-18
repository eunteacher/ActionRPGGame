#include "Notifies/CAnimNotify_DefaultWeapon.h"

#include "Characters/CBaseCharacter.h"

FString UCAnimNotify_DefaultWeapon::GetNotifyName_Implementation() const
{
	return "DefaultWeapon";
}

void UCAnimNotify_DefaultWeapon::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (IsValid(MeshComp->GetOwner<ACBaseCharacter>()))
	{
		MeshComp->GetOwner<ACBaseCharacter>()->SetDefaultWeapon();
	}
}
