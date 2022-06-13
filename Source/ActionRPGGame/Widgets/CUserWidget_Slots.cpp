#include "Widgets/CUserWidget_Slots.h"
#include "Components/Image.h"
#include "CUserWidget_BaseProgressBar.h"

void UCUserWidget_Slots::SetIcon(UTexture2D* InTexture2D, UTexture2D* InAbility01, UTexture2D* InAbility02, UTexture2D* InAbility03, UTexture2D* InAbility04, bool IsDefault)
{
	if(IsDefault)
	{
		WeaponImage->SetVisibility(ESlateVisibility::Hidden);

		AbilitySlot01->HiddenProgressBar();
		AbilitySlot02->HiddenProgressBar();
		AbilitySlot03->HiddenProgressBar();
		AbilitySlot04->HiddenProgressBar();
	}
	else
	{
		if (WeaponImage->GetVisibility() == ESlateVisibility::Hidden)
		{
			WeaponImage->SetVisibility(ESlateVisibility::Visible);

			AbilitySlot01->VisibleProgressBar();
			AbilitySlot02->VisibleProgressBar();
			AbilitySlot03->VisibleProgressBar();
			AbilitySlot04->VisibleProgressBar();
		}

		// WeaponType Icon 변경
		WeaponImage->SetBrushFromTexture(InTexture2D);

		// WeaponType에 맞는 Ability Icon 설정
		AbilitySlot01->ChangedProgressBarImage(InAbility01);
		AbilitySlot02->ChangedProgressBarImage(InAbility02);
		AbilitySlot03->ChangedProgressBarImage(InAbility03);
		AbilitySlot04->ChangedProgressBarImage(InAbility04);
	}
}
