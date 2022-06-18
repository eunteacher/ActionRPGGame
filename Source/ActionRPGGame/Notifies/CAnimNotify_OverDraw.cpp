#include "Notifies/CAnimNotify_OverDraw.h"
#include "Characters/CBaseCharacter.h"
#include "Weapon/CWeapon_Far.h"

FString UCAnimNotify_OverDraw::GetNotifyName_Implementation() const
{
	return "OverDraw";
}

void UCAnimNotify_OverDraw::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (IsValid(MeshComp->GetOwner<ACBaseCharacter>()))
	{
		// Owner 캐릭터를 가져온다.
		ACBaseCharacter* ownerCharacter = MeshComp->GetOwner<ACBaseCharacter>();

		if(ownerCharacter->GetEquipWeaponDataMaps().Contains(ownerCharacter->GetWeaponType()))
		{
			// 현재 Equip인 Weapon을 가져온다.
			ACWeapon_Far* far = Cast<ACWeapon_Far>(ownerCharacter->GetEquipWeaponDataMaps().Find(ownerCharacter->GetWeaponType())->Weapon);
			far->SetIsOverDraw(true);
		}
	}
}
