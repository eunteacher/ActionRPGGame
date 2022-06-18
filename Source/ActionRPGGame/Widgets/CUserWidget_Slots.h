#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CUserWidget_Slots.generated.h"

// 전방 선언
class UOverlay;
class UImage;
class UCUserWidget_AbilitySlot;

UCLASS()
class ACTIONRPGGAME_API UCUserWidget_Slots : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	
	// 무기 변경 시 호출
	UFUNCTION()
	void UpdateSlot(UTexture2D* InWeaponIcon, TArray<class ACAbility*> InAbilities, bool InIsDefault);

	UFUNCTION()
	void OnAbilityActivated(ACAbility* InAbility);

	TArray<UCUserWidget_AbilitySlot*> GetAbilitySlots();
protected:
	UPROPERTY(meta = (BindWidget))
	UOverlay* Overlay;

	UPROPERTY(meta = (BindWidget))
	UImage* Frame;

	UPROPERTY(meta = (BindWidget))
	UImage* Background;

	UPROPERTY(meta = (BindWidget))
	UOverlay* WeaponSlot_Overlay;

	UPROPERTY(meta = (BindWidget))
	UImage* WeaponImage_Background;
	
	UPROPERTY(meta = (BindWidget))
	UImage* WeaponImage;

	UPROPERTY(meta = (BindWidget))
	UCUserWidget_AbilitySlot* AbilitySlot01;
	
	UPROPERTY(meta = (BindWidget))
	UCUserWidget_AbilitySlot* AbilitySlot02;

	UPROPERTY(meta = (BindWidget))
	UCUserWidget_AbilitySlot* AbilitySlot03;

	UPROPERTY(meta = (BindWidget))
	UCUserWidget_AbilitySlot* AbilitySlot04;

};
