#include "Abilities/CAbility_Star.h"

ACAbility_Star::ACAbility_Star()
{
	// Type 초기화
	WeaponType = EWeaponType::Sword;
	AbilityType = EAbilityType::Star;
	MontageType = EMontageType::Star;

	// Ability Icon 초기화
	// Texture2D'/Game/Widgets/Textures/Icon/T_SwordAbility04.T_SwordAbility04'
	const ConstructorHelpers::FObjectFinder<UTexture2D> abilityIconAsset(TEXT("Texture2D'/Game/Widgets/Textures/Icon/T_SwordAbility04.T_SwordAbility04'"));
	if (abilityIconAsset.Succeeded())
	{
		AbilityIcon = abilityIconAsset.Object;
	}
}
