#include "Widgets/CUserWidget_BaseProgressBar.h"
#include "Components/ProgressBar.h"

void UCUserWidget_BaseProgressBar::UpdateValue(float InValue, float InMaxValue)
{
	// 입력받은 값과 입력 받은 값의 최댓값을 나눈다.
	ProgressBar->SetPercent(InValue / InMaxValue);
}

void UCUserWidget_BaseProgressBar::ChangedProgressBarImage(UTexture2D* InTexture2D) const
{
	ProgressBar->WidgetStyle.BackgroundImage.SetResourceObject(InTexture2D);
	ProgressBar->WidgetStyle.FillImage.SetResourceObject(InTexture2D);
}

void UCUserWidget_BaseProgressBar::HiddenProgressBar() const
{
	ProgressBar->SetVisibility(ESlateVisibility::Hidden);
}

void UCUserWidget_BaseProgressBar::VisibleProgressBar() const
{
	ProgressBar->SetVisibility(ESlateVisibility::Visible);
}

