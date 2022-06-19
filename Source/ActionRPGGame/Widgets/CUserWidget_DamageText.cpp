#include "Widgets/CUserWidget_DamageText.h"
#include "Components/TextBlock.h"

void UCUserWidget_DamageText::SetDamageText(FText InText, bool InIsPlayer, bool InIsDamageEffect)
{
	if(InIsPlayer)
	{
		DamageText->SetColorAndOpacity(FSlateColor(FColor(0, 255, 0)));
	}
	else if(InIsDamageEffect)
	{
		DamageText->SetColorAndOpacity(FSlateColor(FColor(0, 255, 255)));
	}

	DamageText->SetText(InText);
}
