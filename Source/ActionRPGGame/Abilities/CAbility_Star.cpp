#include "Abilities/CAbility_Star.h"

ACAbility_Star::ACAbility_Star()
{
	// Type 초기화
	WeaponType = EWeaponType::Sword;
	AbilityType = EAbilityType::Star;
	MontageType = EMontageType::Star;

	// Ability Icon 초기화
	// Texture2D'/Game/Widgets/Textures/Icon/T_StarIcon.T_StarIcon'
	const ConstructorHelpers::FObjectFinder<UTexture2D> abilityIconAsset(TEXT("Texture2D'/Game/Widgets/Textures/Icon/T_StarIcon.T_StarIcon'"));
	if (abilityIconAsset.Succeeded())
	{
		AbilityIcon = abilityIconAsset.Object;
	}
}

void ACAbility_Star::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ACAbility_Star::OnActivation()
{
	Super::OnActivation();
}

void ACAbility_Star::OnProgress()
{
	Super::OnProgress();
}

void ACAbility_Star::OnDeActivation()
{
	Super::OnDeActivation();
}
