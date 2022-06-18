#include "Widgets/CUserWidget_Slots.h"
#include "ActionRPGGame.h"
#include "Components/Image.h"
#include "CUserWidget_AbilitySlot.h"
#include "Abilities/CAbility.h"
#include "Blueprint/WidgetTree.h"
#include "Types/CEnumTypes.h"

void UCUserWidget_Slots::NativeConstruct()
{
	Super::NativeConstruct();

	WeaponImage->SetVisibility(ESlateVisibility::Hidden);
}

void UCUserWidget_Slots::UpdateSlot(UTexture2D* InWeaponIcon, TArray<ACAbility*> InAbilities, bool InIsDefault)
{
	if(InIsDefault)
	{
		// Default가 true인 경우 Slot의 이미지를 전부 Hidden
		
		WeaponImage->SetVisibility(ESlateVisibility::Hidden);

		TArray<UCUserWidget_AbilitySlot*> abilitySlots = GetAbilitySlots();
		for(UCUserWidget_AbilitySlot* abilitySlot : abilitySlots)
		{
			if(IsValid(abilitySlot))
			{
				abilitySlot->HiddenProgressBar();
				abilitySlot->SetAbility(nullptr);
			} // IsValid abilitySlot
		}
	}
	else
	{
		// Default가 false인 경우 Slot의 이미지를 접누 Visible
		
		WeaponImage->SetVisibility(ESlateVisibility::Visible);

		TArray<UCUserWidget_AbilitySlot*> abilitySlots = GetAbilitySlots();
		for(UCUserWidget_AbilitySlot* abilitySlot : abilitySlots)
		{
			abilitySlot->VisibleProgressBar();
		}

		// Icon 변경
		
		// 입력 받은 WeaponIcon으로 변경
		WeaponImage->SetBrushFromTexture(InWeaponIcon);

		// 각 Slot에 순서대로 Ability를 입력한다.
		for(int32 i = 0; i < InAbilities.Num(); i++)
		{
			if (IsValid(InAbilities[i]) && IsValid(abilitySlots[i]) && i < abilitySlots.Num())
			{
				abilitySlots[i]->SetAbility(InAbilities[i]);
			} // if IsValid 
		} // for i
	}
}

void UCUserWidget_Slots::OnAbilityActivated(ACAbility* InAbility)
{
	EAbilityType abilityType = InAbility->GetAbilityType();
	TArray<UCUserWidget_AbilitySlot*> abilitySlots = GetAbilitySlots();

	for(UCUserWidget_AbilitySlot* abilitySlot : abilitySlots)
	{
		if(abilitySlot->GetAbility()->GetAbilityType() == abilityType)
		{
			abilitySlot->SetAvailable(true);
			break;
		} // if type == type
	} // for slot
}

// Ability Slot을 순서대로 배열로 만들어 반환한다.
TArray<UCUserWidget_AbilitySlot*> UCUserWidget_Slots::GetAbilitySlots()
{
	// 반환할 Array 선언
	TArray<UCUserWidget_AbilitySlot*> abilitySlots;
	FString widgetName = "AbilitySlot";
	
	int32 zero = 0;
	int32 index = 1;
	int32 maxIndex = 5; // slot 총 개수 + 1
	
	while(index < maxIndex)
	{
		// 슬릇 이름 만들기 
		FString temp = FString::FromInt(zero) + FString::FromInt(index++);
		FString slotName = widgetName + temp;

		// FindWidget(WidgetName)을 통해 AbilitySlot을 찾는다.
		UCUserWidget_AbilitySlot* abilitySlot = WidgetTree->FindWidget<UCUserWidget_AbilitySlot>(FName(*slotName));
		if(IsValid(abilitySlot))
		{
			abilitySlots.Add(abilitySlot);
		}
		else
		{
			break;
		}
	}
	
	return abilitySlots;
}
