#include "Weapon/CWeapon_Base.h"

#include "Charactets/CBaseCharacter.h"
#include "Components/CMontageComponent.h"
#include "Types/CEnumTypes.h"

ACWeapon_Base::ACWeapon_Base()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(Root);
}
// 무기 장착
// 몽타주 실행 및 캐릭터의 무기 Attach
void ACWeapon_Base::OnEquip()
{
	bEquip = true; // 무기 장착 여부 true
	// State 설정
	GetOwner<ACBaseCharacter>()->SetState(EStateType::Equip); 
	// 무기를 소유한 캐릭터의 Montage 컴포넌트를 가져온다.
	UCMontageComponent* montage = Cast<UCMontageComponent>(GetOwner<ACBaseCharacter>()->GetComponentByClass(UCMontageComponent::StaticClass()));
	if(IsValid(montage))
	{
		// WeaponType에 맞게 몽타주 실행
		if(WeaponType == EWeaponType::Sword)
		{
			montage->PlayMontage(GetOwner<ACBaseCharacter>()->GetCurrentModelType(), EMontageType::Equip_Sword);
		}
		else if(WeaponType == EWeaponType::Bow)
		{
			montage->PlayMontage(GetOwner<ACBaseCharacter>()->GetCurrentModelType(), EMontageType::Equip_Bow);
		}
	}
}
// 무기 해제
void ACWeapon_Base::OnUnequip()
{
	bEquip = false; // 무기 장착 여부 false
	GetOwner<ACBaseCharacter>()->SetState(EStateType::Unequip); 
	// 무기를 소유한 캐릭터의 Montage 컴포넌트를 가져온다.
	UCMontageComponent* montage = Cast<UCMontageComponent>(GetOwner<ACBaseCharacter>()->GetComponentByClass(UCMontageComponent::StaticClass()));
	if(IsValid(montage))
	{
		// WeaponType에 맞게 몽타주 실행
		if(WeaponType == EWeaponType::Sword)
		{
			montage->PlayMontage(GetOwner<ACBaseCharacter>()->GetCurrentModelType(), EMontageType::Unequip_Sword);
		}
		else if(WeaponType == EWeaponType::Bow)
		{
			montage->PlayMontage(GetOwner<ACBaseCharacter>()->GetCurrentModelType(), EMontageType::Unequip_Bow);
		}
	}
}

void ACWeapon_Base::OnAttach(FName InSocketName)
{
	ACBaseCharacter* ownerCharacter = GetOwner<ACBaseCharacter>();
	if (IsValid(ownerCharacter))
	{
		GetOwner()->AttachToComponent
		(
			ownerCharacter->GetMesh(),
			FAttachmentTransformRules(EAttachmentRule::KeepRelative, false),
			InSocketName
		);
	}
}


