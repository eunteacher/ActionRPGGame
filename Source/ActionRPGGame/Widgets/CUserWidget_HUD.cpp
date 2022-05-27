#include "Widgets/CUserWidget_HUD.h"
#include "Widgets/CUserWidget_BaseProgressBar.h"

void UCUserWidget_HUD::UpdateStamina(float InStamina, float InMaxStamina)
{
	// 스테미너 UpdateValue() 함수 호출
	StaminaBar->UpdateValue(InStamina, InMaxStamina);
}

void UCUserWidget_HUD::UpdateHealth(float InHealth, float InMaxHealth)
{
	// Health UpdateValue() 함수 호출
	HealthBar->UpdateValue(InHealth, InMaxHealth);
}

void UCUserWidget_HUD::UpdateMana(float InMana, float InMaxMana)
{
	// Mana UpdateValue() 함수 호출
	ManaBar->UpdateValue(InMana, InMaxMana);
}

