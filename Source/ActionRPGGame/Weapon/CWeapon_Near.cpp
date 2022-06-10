#include "Weapon/CWeapon_Near.h"
#include "ActionRPGGame.h"
#include "Charactets/CBaseCharacter.h"
#include "Components/CMontageComponent.h"
#include "Components/CSoundComponent.h"

ACWeapon_Near::ACWeapon_Near()
{
	// 멤버 변수 초기화
	CanCombo = false;
}

void ACWeapon_Near::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACWeapon_Near::OnReset()
{
	Super::OnReset();
	CLog::Log("Near OnReset");
	CanCombo = false;
	IsAttack = false;
	AttackType = EAttackType::Near_Combo1;
}

void ACWeapon_Near::OnAttack()
{
	CLog::Log("OnAttack");
	
	// 장착되어 있을 경우
	if(IsEquip)
	{
		if(!IsAttack) // IsAttack이 false인 경우
		{
			// 콤보 공격 사용을 위해서 IsAttack을 true로 변경하여 다시 못들어오게 한다.
			IsAttack = true; 
			// 공격 타입을 콤보 공격 1로 설정
			AttackType = EAttackType::Near_Combo1;
		
			UCMontageComponent* montage = Cast<UCMontageComponent>(GetOwner<ACBaseCharacter>()->GetComponentByClass(UCMontageComponent::StaticClass()));
			UCSoundComponent* sound = Cast<UCSoundComponent>(GetOwner<ACBaseCharacter>()->GetComponentByClass(UCSoundComponent::StaticClass()));

			if(UseWeaponDataMaps.Contains(AttackType) && IsValid(montage) && IsValid(sound))
			{
				// AttackType에 맞는 몽타주 실행
				montage->PlayMontage(UseWeaponDataMaps.Find(AttackType)->MontageType);
				// Battle 사운드 실행
				sound->PlayAttackSound();
			}			
		}
		else
		{
			// 공격 호출이 들어왓기 때문에 CanCombo를 true
			CanCombo = true;
		}
	}
}

void ACWeapon_Near::ComboAttack()
{
	// CanCombo true인 경우
	if(CanCombo)
	{
		// 다시 못들어오게 하기 위해 CanCombo를 false
		CanCombo = false;

		// Combo1일 경우 Combo2로, Combo2일 경우 Combo3으로
		if (AttackType == EAttackType::Near_Combo1)
		{
			AttackType = EAttackType::Near_Combo2;
		}
		else if(AttackType == EAttackType::Near_Combo2)
		{
			AttackType = EAttackType::Near_Combo3;
		}

		// Character의 Montage와 Sound 컴포넌트를 가져온다.
		UCMontageComponent* montage = Cast<UCMontageComponent>(GetOwner<ACBaseCharacter>()->GetComponentByClass(UCMontageComponent::StaticClass()));
		UCSoundComponent* sound = Cast<UCSoundComponent>(GetOwner<ACBaseCharacter>()->GetComponentByClass(UCSoundComponent::StaticClass()));

		if(UseWeaponDataMaps.Contains(AttackType) && IsValid(montage) && IsValid(sound))
		{
			// AttackType에 맞는 몽타주 실행
			montage->PlayMontage(UseWeaponDataMaps.Find(AttackType)->MontageType);
			// Battle 사운드 실행
			sound->PlayAttackSound();
		}
	}
}

