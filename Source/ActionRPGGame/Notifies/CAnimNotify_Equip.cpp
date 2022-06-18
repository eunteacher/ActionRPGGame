#include "Notifies/CAnimNotify_Equip.h"
#include "ActionRPGGame.h"
#include "Characters/CBaseCharacter.h"
#include "Weapon/CWeapon.h"

FString UCAnimNotify_Equip::GetNotifyName_Implementation() const
{
	return "Equip";
}

void UCAnimNotify_Equip::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (IsValid(MeshComp->GetOwner<ACBaseCharacter>()))
	{
		CLog::Log("Notify");
		// Owner 캐릭터를 가져온다.
		ACBaseCharacter* ownerCharacter = MeshComp->GetOwner<ACBaseCharacter>();

		if(ownerCharacter->GetEquipWeaponDataMaps().Contains(ownerCharacter->GetWeaponType()))
		{
			// socketName을 가져온다.
			const FName socketName = ownerCharacter->GetEquipWeaponDataMaps().Find(ownerCharacter->GetWeaponType())->WeaponSocketName;
			// 현재 Equip인 Weapon을 가져온다.
			ACWeapon* weapon = ownerCharacter->GetEquipWeaponDataMaps().Find(ownerCharacter->GetWeaponType())->Weapon;
			weapon->OnAttach(socketName);
		}
	}
}
