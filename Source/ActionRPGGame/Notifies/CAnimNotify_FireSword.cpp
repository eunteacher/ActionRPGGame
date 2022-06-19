#include "Notifies/CAnimNotify_FireSword.h"
#include "Abilities/CAbility.h"
#include "Characters/CBaseCharacter.h"

FString UCAnimNotify_FireSword::GetNotifyName_Implementation() const
{
	return "FireSword";
}

void UCAnimNotify_FireSword::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (IsValid(MeshComp->GetOwner<ACBaseCharacter>()))
	{
		// Owner 캐릭터를 가져온다.
		ACBaseCharacter* ownerCharacter = MeshComp->GetOwner<ACBaseCharacter>();
		if(ownerCharacter->GetEquipAbilityDataMaps().Contains(ownerCharacter->GetAbilityType()))
		{
			ownerCharacter->GetEquipAbilityDataMaps().Find(ownerCharacter->GetAbilityType())->Ability->OnProgress();
		}
	}
}
