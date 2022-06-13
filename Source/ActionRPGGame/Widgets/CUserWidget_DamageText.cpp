#include "Widgets/CUserWidget_DamageText.h"
#include "Components/TextBlock.h"

void UCUserWidget_DamageText::SetDamageText(FText InText, bool IsPlayer)
{
	if(IsPlayer)
	{
		DamageText->SetColorAndOpacity(FSlateColor(FColor(0, 255, 0)));
	}

	DamageText->SetText(InText);
}
