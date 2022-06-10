#include "Notifies/CAnimNotify_OverDraw.h"
#include "Charactets/CBaseCharacter.h"
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
		// OnwingWeaponData를 가져온다.
		TMap<EWeaponType, FEquipedWeaponData> equipeWeaponDataMap = ownerCharacter->GetEquipedWeaponDataMaps();
		// 가져온 Map에서 Weapon 클래스를 찾아 저장한다.
		ACWeapon_Far* far = Cast<ACWeapon_Far>(equipeWeaponDataMap.Find(ownerCharacter->GetWeaponType())->Weapon);
		far->SetIsOverDraw(true);
	}
}
