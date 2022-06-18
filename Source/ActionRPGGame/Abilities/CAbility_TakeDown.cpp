#include "Abilities/CAbility_TakeDown.h"

ACAbility_TakeDown::ACAbility_TakeDown()
{
	// Type 초기화
	WeaponType = EWeaponType::Sword;
	AbilityType = EAbilityType::TakeDown;
	MontageType = EMontageType::TakeDown;

	// Ability Icon 초기화
	// Texture2D'/Game/Widgets/Textures/Icon/T_SwordAbility03.T_SwordAbility03'
	const ConstructorHelpers::FObjectFinder<UTexture2D> abilityIconAsset(TEXT("Texture2D'/Game/Widgets/Textures/Icon/T_SwordAbility03.T_SwordAbility03'"));
	if (abilityIconAsset.Succeeded())
	{
		AbilityIcon = abilityIconAsset.Object;
	}
}
