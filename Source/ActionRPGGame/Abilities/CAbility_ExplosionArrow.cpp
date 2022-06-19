#include "Abilities/CAbility_ExplosionArrow.h"

ACAbility_ExplosionArrow::ACAbility_ExplosionArrow()
{
	// Type 초기화
	WeaponType = EWeaponType::Bow;
	AbilityType = EAbilityType::ExplosionArrow;
	MontageType = EMontageType::ExplosionArrow;
	
	// 데미지, 쿨다운, 코스트, 지속시간 초기화
	Damage = 0.2f;
	CoolDown = 10.0f;
	ManaCost = 50.0f;
	Duration = 5;

	// Ability Icon 초기화
	// Texture2D'/Game/Widgets/Textures/Icon/T_ExplosionArrowIcon.T_ExplosionArrowIcon'
	const ConstructorHelpers::FObjectFinder<UTexture2D> abilityIconAsset(TEXT("Texture2D'/Game/Widgets/Textures/Icon/T_ExplosionArrowIcon.T_ExplosionArrowIcon'"));
	if (abilityIconAsset.Succeeded())
	{
		AbilityIcon = abilityIconAsset.Object;
	}
}

void ACAbility_ExplosionArrow::OnActivation()
{
	Super::OnActivation();
}

void ACAbility_ExplosionArrow::OnProgress()
{
	Super::OnProgress();
}

void ACAbility_ExplosionArrow::OnDeActivation()
{
	Super::OnDeActivation();
}
