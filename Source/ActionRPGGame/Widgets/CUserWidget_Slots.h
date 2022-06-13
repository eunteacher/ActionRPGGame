#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CUserWidget_Slots.generated.h"

// 전방 선언
class UOverlay;
class UImage;
class UCUserWidget_BaseProgressBar;

UCLASS()
class ACTIONRPGGAME_API UCUserWidget_Slots : public UUserWidget
{
	GENERATED_BODY()

public:
	// 무기 변경 시 호출
	// 입력으로 변경할 이미지들과 WeaponType이 Default의 여부를 받는다.
	UFUNCTION()
	void SetIcon(UTexture2D* InWeapon, UTexture2D* InAbility01, UTexture2D* InAbility02, UTexture2D* InAbility03, UTexture2D* InAbility04, bool IsDefault);
	
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
	UCUserWidget_BaseProgressBar* AbilitySlot01;
	
	UPROPERTY(meta = (BindWidget))
	UCUserWidget_BaseProgressBar* AbilitySlot02;

	UPROPERTY(meta = (BindWidget))
	UCUserWidget_BaseProgressBar* AbilitySlot03;

	UPROPERTY(meta = (BindWidget))
	UCUserWidget_BaseProgressBar* AbilitySlot04;
};
