#include "Notifies/CAnimNotify_UnEquip.h"
#include "ActionRPGGame.h"
#include "Charactets/CBaseCharacter.h"
#include "Weapon/CWeapon_Base.h"

FString UCAnimNotify_UnEquip::GetNotifyName_Implementation() const
{
	return "UnEquip";
}

void UCAnimNotify_UnEquip::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (IsValid(MeshComp->GetOwner<ACBaseCharacter>()))
	{
		// Owner 캐릭터를 가져온다.
		ACBaseCharacter* ownerCharacter = MeshComp->GetOwner<ACBaseCharacter>();
		// OnwingWeaponData를 가져온다.
		TMap<EWeaponType, FEquipedWeaponData> owningWeaponDataMap = ownerCharacter->GetEquipedWeaponDataMaps();
		// 가져온 Map에서 Weapon 클래스를 찾아 저장한다.
		ACWeapon_Base* weapon = owningWeaponDataMap.Find(ownerCharacter->GetWeaponType())->Weapon;
		// 소켓 이름
		const FName socketName = owningWeaponDataMap.Find(ownerCharacter->GetWeaponType())->WeaponHolsterSocketName;
		// Weapon 클래스의 OnAttach() 호출
		weapon->OnAttach(socketName);
	}
}
