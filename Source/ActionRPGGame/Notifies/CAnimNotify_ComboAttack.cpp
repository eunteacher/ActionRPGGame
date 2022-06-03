// Fill out your copyright notice in the Description page of Project Settings.


#include "Notifies/CAnimNotify_ComboAttack.h"
#include "Charactets/CBaseCharacter.h"
#include "Weapon/CWeapon_Sword.h"

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
		// OnwingWeaponData를 가져온다.
		TMap<EWeaponType, FEquipedWeaponData> equipeWeaponDataMap = ownerCharacter->GetEquipedWeaponDataMaps();
		// 가져온 Map에서 Weapon 클래스를 찾아 저장한다.
		ACWeapon_Sword* sword = Cast<ACWeapon_Sword>(equipeWeaponDataMap.Find(ownerCharacter->GetWeaponType())->Weapon);
		// ACWeapon_Sword 클래스의 ComboAttack() 호출
		sword->ComboAttack();
	}
}
