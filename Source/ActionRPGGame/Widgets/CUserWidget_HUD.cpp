#include "Widgets/CUserWidget_HUD.h"
#include "ActionRPGGame.h"
#include "CUserWidget_Slots.h"
#include "Characters/CBaseCharacter.h"
#include "Widgets/CUserWidget_BaseProgressBar.h"
#include "Characters/CPlayerController.h"
#include "Abilities/CAbility.h"
#include "Blueprint/WidgetTree.h"

void UCUserWidget_HUD::NativeConstruct()
{
	Super::NativeConstruct();

	if(IsValid(GetOwningPlayer<ACPlayerController>()))
	{
		GetOwningPlayer<ACPlayerController>()->OnHealthChanged.AddDynamic(this, &UCUserWidget_HUD::UpdateHealth);
		GetOwningPlayer<ACPlayerController>()->OnManaChanged.AddDynamic(this, &UCUserWidget_HUD::UpdateMana);
		GetOwningPlayer<ACPlayerController>()->OnStaminaChanged.AddDynamic(this, &UCUserWidget_HUD::UpdateStamina);
		GetOwningPlayer<ACPlayerController>()->OnWeaponChanged.AddDynamic(this, &UCUserWidget_HUD::UpdateSlot);
		GetOwningPlayer<ACPlayerController>()->OnAbilityActivated.AddDynamic(this, &UCUserWidget_HUD::OnAbilityActivated);
	}
}

void UCUserWidget_HUD::UpdateStamina(float& InStamina, float& InMaxStamina)
{
	// 스테미너 UpdateValue() 함수 호출
	StaminaBar->UpdateValue(InStamina, InMaxStamina);
}

void UCUserWidget_HUD::UpdateHealth(float& InHealth, float& InMaxHealth)
{
	// Health UpdateValue() 함수 호출
	HealthBar->UpdateValue(InHealth, InMaxHealth);
}

void UCUserWidget_HUD::UpdateMana(float& InMana, float& InMaxMana)
{
	// Mana UpdateValue() 함수 호출
	ManaBar->UpdateValue(InMana, InMaxMana);
}

void UCUserWidget_HUD::UpdateSlot(UTexture2D* InWeaponIcon, TArray<ACAbility*> InAbilities, bool InIsDefault)
{
	Slots->UpdateSlot(InWeaponIcon, InAbilities, InIsDefault);
}

void UCUserWidget_HUD::OnAbilityActivated(ACAbility* InAbility)
{
	Slots->OnAbilityActivated(InAbility);
}


