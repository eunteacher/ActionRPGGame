#include "Widgets/CUserWidget_BaseProgressBar.h"
#include "Components/ProgressBar.h"

void UCUserWidget_BaseProgressBar::UpdateValue(float InValue, float InMaxValue)
{
	// 입력받은 값과 입력 받은 값의 최댓값을 나눈다.
	ProgressBar->SetPercent(InValue / InMaxValue);
}
