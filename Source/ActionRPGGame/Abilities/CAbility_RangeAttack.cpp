#include "Abilities/CAbility_RangeAttack.h"

ACAbility_RangeAttack::ACAbility_RangeAttack()
{
	// Type 초기화
	WeaponType = EWeaponType::Sword;
	AbilityType = EAbilityType::RangeAttack;
	MontageType = EMontageType::RangeAttack;

	// Ability Icon 초기화
	// Texture2D'/Game/Widgets/Textures/Icon/T_RangeAttackIcon.T_RangeAttackIcon'
	const ConstructorHelpers::FObjectFinder<UTexture2D> abilityIconAsset(TEXT("Texture2D'/Game/Widgets/Textures/Icon/T_RangeAttackIcon.T_RangeAttackIcon'"));
	if (abilityIconAsset.Succeeded())
	{
		AbilityIcon = abilityIconAsset.Object;
	}
}

void ACAbility_RangeAttack::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ACAbility_RangeAttack::OnActivation()
{
	Super::OnActivation();
}

void ACAbility_RangeAttack::OnProgress()
{
	Super::OnProgress();
}

void ACAbility_RangeAttack::OnDeActivation()
{
	Super::OnDeActivation();
}
