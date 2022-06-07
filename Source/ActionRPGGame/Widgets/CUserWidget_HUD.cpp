#include "Widgets/CUserWidget_HUD.h"

#include "CUserWidget_Slots.h"
#include "Widgets/CUserWidget_BaseProgressBar.h"
#include "Charactets/CPlayerController.h"

void UCUserWidget_HUD::Bind()
{
	if(IsValid(GetOwningPlayer<ACPlayerController>()))
	{
		GetOwningPlayer<ACPlayerController>()->OnHealthChanged.AddDynamic(this, &UCUserWidget_HUD::UpdateHealth);
		GetOwningPlayer<ACPlayerController>()->OnManaChanged.AddDynamic(this, &UCUserWidget_HUD::UpdateMana);
		GetOwningPlayer<ACPlayerController>()->OnStaminaChanged.AddDynamic(this, &UCUserWidget_HUD::UpdateStamina);
		GetOwningPlayer<ACPlayerController>()->OnSlotChanged.AddDynamic(this,&UCUserWidget_HUD::UpdateSlot);
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

void UCUserWidget_HUD::UpdateSlot(const FWeaponIconInfo& InIconInfo, bool IsDefault)
{
	Slots->SetIcon(InIconInfo.WeaponIcon, InIconInfo.Ability1_Icon, InIconInfo.Ability2_Icon, InIconInfo.Ability3_Icon, InIconInfo.Ability4_Icon, IsDefault);
}
