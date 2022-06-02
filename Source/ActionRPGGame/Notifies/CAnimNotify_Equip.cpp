#include "Notifies/CAnimNotify_Equip.h"
#include "Charactets/CBaseCharacter.h"
#include "ActionRPGGame.h"
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
		// OnwingWeaponData를 가져온다.
		TMap<EWeaponType, FOwningWeapon> owningWeaponDataMap = ownerCharacter->GetOwningWeaponDataMaps();
		// 가져온 Map에서 Weapon 클래스를 찾아 저장한다.
		ACWeapon_Base* weapon = owningWeaponDataMap.Find(ownerCharacter->GetWeapon())->Weapon;
		// 소켓 이름 
		const FName socketName = owningWeaponDataMap.Find(ownerCharacter->GetWeapon())->WeaponSocketName;
		// Weapon 클래스의 OnAttach() 호출
		weapon->OnAttach(socketName);
	}
}
