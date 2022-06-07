#include "Widgets/CUserWidget_Slots.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"

void UCUserWidget_Slots::SetIcon(UTexture2D* InTexture2D, UTexture2D* InAbility1, UTexture2D* InAbility2, UTexture2D* InAbility3, UTexture2D* InAbility4, bool IsDefault)
{
	if(IsDefault)
	{
		WeaponImage->SetVisibility(ESlateVisibility::Hidden);

		AbilitySlot1->SetVisibility(ESlateVisibility::Hidden);
		AbilitySlot2->SetVisibility(ESlateVisibility::Hidden);
		AbilitySlot3->SetVisibility(ESlateVisibility::Hidden);
		AbilitySlot4->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		if (WeaponImage->GetVisibility() == ESlateVisibility::Hidden)
		{
			WeaponImage->SetVisibility(ESlateVisibility::Visible);

			AbilitySlot1->SetVisibility(ESlateVisibility::Visible);
			AbilitySlot2->SetVisibility(ESlateVisibility::Visible);
			AbilitySlot3->SetVisibility(ESlateVisibility::Visible);
			AbilitySlot4->SetVisibility(ESlateVisibility::Visible);
		}

		// WeaponType Icon 변경
		WeaponImage->SetBrushFromTexture(InTexture2D);

		// WeaponType에 맞는 Icon 설정
		AbilitySlot1->WidgetStyle.BackgroundImage.SetResourceObject(InAbility1);
		AbilitySlot1->WidgetStyle.FillImage.SetResourceObject(InAbility1);

		AbilitySlot2->WidgetStyle.BackgroundImage.SetResourceObject(InAbility2);
		AbilitySlot2->WidgetStyle.FillImage.SetResourceObject(InAbility2);

		AbilitySlot3->WidgetStyle.BackgroundImage.SetResourceObject(InAbility3);
		AbilitySlot3->WidgetStyle.FillImage.SetResourceObject(InAbility3);

		AbilitySlot4->WidgetStyle.BackgroundImage.SetResourceObject(InAbility4);
		AbilitySlot4->WidgetStyle.FillImage.SetResourceObject(InAbility4);
	}
}
