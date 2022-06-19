#include "Abilities/CAbility_RainArrow.h"

ACAbility_RainArrow::ACAbility_RainArrow()
{
	// Type 초기화
	WeaponType = EWeaponType::Bow;
	AbilityType = EAbilityType::RainArrow;
	MontageType = EMontageType::RainArrow;
	
	// 데미지, 쿨다운, 코스트, 지속시간 초기화
	Damage = 0.2f;
	CoolDown = 10.0f;
	ManaCost = 50.0f;
	Duration = 5;

	// Ability Icon 초기화
	// Texture2D'/Game/Widgets/Textures/Icon/T_RainArrowIcon.T_RainArrowIcon'
	const ConstructorHelpers::FObjectFinder<UTexture2D> abilityIconAsset(TEXT("Texture2D'/Game/Widgets/Textures/Icon/T_RainArrowIcon.T_RainArrowIcon'"));
	if (abilityIconAsset.Succeeded())
	{
		AbilityIcon = abilityIconAsset.Object;
	}
}

void ACAbility_RainArrow::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ACAbility_RainArrow::OnActivation()
{
	Super::OnActivation();
}

void ACAbility_RainArrow::OnProgress()
{
	Super::OnProgress();
}

void ACAbility_RainArrow::OnDeActivation()
{
	Super::OnDeActivation();
}
