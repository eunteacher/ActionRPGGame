#include "Widgets/CUserWidget_AbilitySlot.h"
#include "ActionRPGGame.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Kismet/KismetTextLibrary.h"
#include "Abilities/CAbility.h"

void UCUserWidget_AbilitySlot::NativeConstruct()
{
	Super::NativeConstruct();

	ProgressBar->SetVisibility(ESlateVisibility::Hidden);
	RemainAbilityTimeText->SetVisibility(ESlateVisibility::Hidden);

	IsAvailable = false;

	Value = 0.0f;
	MaxValue = 0.0f;

	IsTimer = true;
	AvailableAbilityTime = 0;
	RemainAbilityTime = 0;
}

void UCUserWidget_AbilitySlot::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (IsAvailable)
	{
		Value += InDeltaTime;
		ProgressBar->SetPercent(Value / MaxValue);

		RemainAbilityTimeText->SetText(UKismetTextLibrary::Conv_IntToText(RemainAbilityTime));

		if (IsTimer)
		{
			IsTimer = false;
			FTimerHandle waitHandle;
			GetWorld()->GetTimerManager().SetTimer(waitHandle, FTimerDelegate::CreateLambda([&]()
			{
				RemainAbilityTime--;
				IsTimer = true;
			}), 1.0f, false);
		}

		if(RemainAbilityTime == -1)
		{
			RemainAbilityTimeText->SetVisibility(ESlateVisibility::Hidden);
			Ability->OnDeActivation();
			
			// 한번만 들어오게 하기 위해서 --를 한번 더 
			RemainAbilityTime--;
		}
		
		if(Value > MaxValue)
		{
			Reset();
		}
	}
}

// ProgressBar의 Image를 변경하는 함수 
void UCUserWidget_AbilitySlot::ChangedProgressBarImage(UTexture2D* InTexture2D) const
{
	ProgressBar->WidgetStyle.BackgroundImage.SetResourceObject(InTexture2D);
	ProgressBar->WidgetStyle.FillImage.SetResourceObject(InTexture2D);
}

// Slots에서 사용 
// ProgressBar의 Visibility를 Hidden으로 변경
void UCUserWidget_AbilitySlot::HiddenProgressBar() const
{
	ProgressBar->SetVisibility(ESlateVisibility::Hidden);
}

// Slots에서 사용 
// ProgressBar의 Visibility를 Visible 변경
void UCUserWidget_AbilitySlot::VisibleProgressBar() const
{
	ProgressBar->SetVisibility(ESlateVisibility::Visible);
}

void UCUserWidget_AbilitySlot::SetAvailable(bool InIsAvailable)
{
	RemainAbilityTimeText->SetVisibility(ESlateVisibility::Visible);
	IsAvailable = InIsAvailable;
}

void UCUserWidget_AbilitySlot::SetAbility(ACAbility* InAbility)
{
	Ability = InAbility;

	if (IsValid(Ability))
	{
		AvailableAbilityTime = InAbility->GetDuration();
		RemainAbilityTime = InAbility->GetDuration();
		MaxValue = InAbility->GetCoolDown();

		CLog::Print(AvailableAbilityTime);
		CLog::Print(RemainAbilityTime);
		CLog::Print(MaxValue);

		ChangedProgressBarImage(Ability->GetAbilityIcon());
	}
}

void UCUserWidget_AbilitySlot::Reset()
{
	IsAvailable = false;
	Value = 0.0f;
	RemainAbilityTime = AvailableAbilityTime;

	ProgressBar->SetPercent(Value / MaxValue);

	Ability->SetIsAvailable(true);
}
