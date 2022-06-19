#include "Abilities/CAbility_PenetratingArrow.h"

ACAbility_PenetratingArrow::ACAbility_PenetratingArrow()
{
	// Type 초기화
	WeaponType = EWeaponType::Bow;
	AbilityType = EAbilityType::PenetratingArrow;
	MontageType = EMontageType::PenetratingArrow;
	
	// 데미지, 쿨다운, 코스트, 지속시간 초기화
	Damage = 0.2f;
	CoolDown = 10.0f;
	ManaCost = 50.0f;
	Duration = 5;

	// Ability Icon 초기화
	// Texture2D'/Game/Widgets/Textures/Icon/T_PenetratingArrowIcon.T_PenetratingArrowIcon'
	const ConstructorHelpers::FObjectFinder<UTexture2D> abilityIconAsset(TEXT("Texture2D'/Game/Widgets/Textures/Icon/T_PenetratingArrowIcon.T_PenetratingArrowIcon'"));
	if (abilityIconAsset.Succeeded())
	{
		AbilityIcon = abilityIconAsset.Object;
	}
}

void ACAbility_PenetratingArrow::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ACAbility_PenetratingArrow::OnActivation()
{
	Super::OnActivation();
}

void ACAbility_PenetratingArrow::OnProgress()
{
	Super::OnProgress();
}

void ACAbility_PenetratingArrow::OnDeActivation()
{
	Super::OnDeActivation();
}
