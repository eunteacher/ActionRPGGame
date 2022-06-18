#include "Notifies/CAnimNotify_ComboAttack.h"
#include "ActionRPGGame.h"
#include "Characters/CBaseCharacter.h"
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
		if(ownerCharacter->GetEquipWeaponDataMaps().Contains(ownerCharacter->GetWeaponType()))
		{
			ACWeapon_Near* near = Cast<ACWeapon_Near>(ownerCharacter->GetEquipWeaponDataMaps().Find(ownerCharacter->GetWeaponType())->Weapon);
			near->ComboAttack();
		}
	}
}
