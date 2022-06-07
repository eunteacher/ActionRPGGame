#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CUserWidget_Slots.generated.h"

// 전방 선언
class UOverlay;
class UImage;
class UProgressBar;

UCLASS()
class ACTIONRPGGAME_API UCUserWidget_Slots : public UUserWidget
{
	GENERATED_BODY()

public:
	// 무기 변경 시 호출
	// 입력으로 변경할 이미지들과 WeaponType이 Default의 여부를 받는다.
	UFUNCTION()
	void SetIcon(UTexture2D* InWeapon, UTexture2D* InAbility1, UTexture2D* InAbility2, UTexture2D* InAbility3, UTexture2D* InAbility4, bool IsDefault);
	
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
	UOverlay* AbilitySlot1_Overlay;

	UPROPERTY(meta = (BindWidget))
	UImage* AbilitySlot1_Background;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* AbilitySlot1;

	UPROPERTY(meta = (BindWidget))
	UOverlay* AbilitySlot2_Overlay;

	UPROPERTY(meta = (BindWidget))
	UImage* AbilitySlot2_Background;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* AbilitySlot2;

	UPROPERTY(meta = (BindWidget))
	UOverlay* AbilitySlot3_Overlay;

	UPROPERTY(meta = (BindWidget))
	UImage* AbilitySlot3_Background;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* AbilitySlot3;

	UPROPERTY(meta = (BindWidget))
	UOverlay* AbilitySlot4_Overlay;

	UPROPERTY(meta = (BindWidget))
	UImage* AbilitySlot4_Background;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* AbilitySlot4;

};
