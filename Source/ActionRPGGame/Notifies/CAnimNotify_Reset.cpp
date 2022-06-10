#include "Notifies/CAnimNotify_Reset.h"
#include "Charactets/CBaseCharacter.h"
#include "Weapon/CWeapon_Base.h"
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
		// OnwingWeaponData를 가져온다.
		TMap<EWeaponType, FEquipedWeaponData> owningWeaponDataMap = ownerCharacter->GetEquipedWeaponDataMaps();
		// 가져온 Map에서 Weapon 클래스를 찾아 저장한다.
		ACWeapon_Base* weapon = owningWeaponDataMap.Find(ownerCharacter->GetWeaponType())->Weapon;
		// Wweapon의 Reset()을 호출한다.
		weapon->OnReset();
	}
}
