#include "Notifies/CAnimNotify_ComboAttack.h"
#include "ActionRPGGame.h"
#include "Charactets/CBaseCharacter.h"
#include "Weapon/CWeapon_Near.h"

FString UCAnimNotify_ComboAttack::GetNotifyName_Implementation() const
{
	return "ComboAttack";
}

void UCAnimNotify_ComboAttack::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (IsValid(MeshComp->GetOwner<ACBaseCharacter>()))
	{
		// Owner 캐릭터를 가져온다.
		ACBaseCharacter* ownerCharacter = MeshComp->GetOwner<ACBaseCharacter>();
		// EquipedWeaponData를 가져온다.
		TMap<EWeaponType, FEquipedWeaponData> equipeWeaponDataMap = ownerCharacter->GetEquipedWeaponDataMaps();
		// 가져온 Map에서 Weapon 클래스를 찾아 저장한다.
		ACWeapon_Near* near = Cast<ACWeapon_Near>(equipeWeaponDataMap.Find(ownerCharacter->GetWeaponType())->Weapon);
		// ACWeapon_Near 클래스의 ComboAttack() 호출
		near->ComboAttack();
	}
}
