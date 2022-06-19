#include "Abilities/CAbility_FireArrow.h"

ACAbility_FireArrow::ACAbility_FireArrow()
{
	// Type 초기화
	WeaponType = EWeaponType::Bow;
	AbilityType = EAbilityType::FireArrow;
	MontageType = EMontageType::FireArrow;
	
	// 데미지, 쿨다운, 코스트, 지속시간 초기화
	Damage = 0.2f;
	CoolDown = 10.0f;
	ManaCost = 50.0f;
	Duration = 5;

	// Ability Icon 초기화
	// Texture2D'/Game/Widgets/Textures/Icon/T_FireArrowIcon.T_FireArrowIcon'
	const ConstructorHelpers::FObjectFinder<UTexture2D> abilityIconAsset(TEXT("Texture2D'/Game/Widgets/Textures/Icon/T_FireArrowIcon.T_FireArrowIcon'"));
	if (abilityIconAsset.Succeeded())
	{
		AbilityIcon = abilityIconAsset.Object;
	}

}

void ACAbility_FireArrow::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ACAbility_FireArrow::OnActivation()
{
	Super::OnActivation();
}

void ACAbility_FireArrow::OnProgress()
{
	Super::OnProgress();
}

void ACAbility_FireArrow::OnDeActivation()
{
	Super::OnDeActivation();
}
