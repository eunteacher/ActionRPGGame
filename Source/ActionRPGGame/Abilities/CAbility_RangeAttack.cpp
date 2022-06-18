#include "Abilities/CAbility_RangeAttack.h"

ACAbility_RangeAttack::ACAbility_RangeAttack()
{
	// Type 초기화
	WeaponType = EWeaponType::Sword;
	AbilityType = EAbilityType::RangeAttack;
	MontageType = EMontageType::RangeAttack;

	// Ability Icon 초기화
	// Texture2D'/Game/Widgets/Textures/Icon/T_SwordAbility02.T_SwordAbility02'
	const ConstructorHelpers::FObjectFinder<UTexture2D> abilityIconAsset(TEXT("Texture2D'/Game/Widgets/Textures/Icon/T_SwordAbility02.T_SwordAbility02'"));
	if (abilityIconAsset.Succeeded())
	{
		AbilityIcon = abilityIconAsset.Object;
	}
}
