#include "Abilities/CAbility_TakeDown.h"

ACAbility_TakeDown::ACAbility_TakeDown()
{
	// Type 초기화
	WeaponType = EWeaponType::Sword;
	AbilityType = EAbilityType::TakeDown;
	MontageType = EMontageType::TakeDown;

	// Ability Icon 초기화
	// Texture2D'/Game/Widgets/Textures/Icon/T_TakeDownIcon.T_TakeDownIcon'
	const ConstructorHelpers::FObjectFinder<UTexture2D> abilityIconAsset(TEXT("Texture2D'/Game/Widgets/Textures/Icon/T_TakeDownIcon.T_TakeDownIcon'"));
	if (abilityIconAsset.Succeeded())
	{
		AbilityIcon = abilityIconAsset.Object;
	}
}

void ACAbility_TakeDown::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ACAbility_TakeDown::OnActivation()
{
	Super::OnActivation();
}

void ACAbility_TakeDown::OnProgress()
{
	Super::OnProgress();
}

void ACAbility_TakeDown::OnDeActivation()
{
	Super::OnDeActivation();
}
