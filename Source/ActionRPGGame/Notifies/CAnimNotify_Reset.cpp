#include "Notifies/CAnimNotify_Reset.h"
#include "Characters/CBaseCharacter.h"
#include "Weapon/CWeapon.h"
#include "ActionRPGGame.h"

FString UCAnimNotify_Reset::GetNotifyName_Implementation() const
{
	return "Reset";
}

void UCAnimNotify_Reset::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (IsValid(MeshComp->GetOwner<ACBaseCharacter>()))
	{
		// Owner 캐릭터를 가져온다.
		ACBaseCharacter* ownerCharacter = MeshComp->GetOwner<ACBaseCharacter>();
		if(ownerCharacter->GetEquipWeaponDataMaps().Contains(ownerCharacter->GetWeaponType()))
		{
			// 현재 Equip인 Weapon을 가져온다.
			ACWeapon* weapon = ownerCharacter->GetEquipWeaponDataMaps().Find(ownerCharacter->GetWeaponType())->Weapon;
			weapon->OnReset();
		}
	}
}
