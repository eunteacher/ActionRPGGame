#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Types/CEnumTypes.h"
#include "Types/CStructTypes.h"
#include "CUserWidget_HUD.generated.h"

// 전방 선언
class UCanvasPanel;
class UCUserWidget_BaseProgressBar;

UCLASS()
class ACTIONRPGGAME_API UCUserWidget_HUD : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	
protected:
	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* CanvasPanel;

	UPROPERTY(meta = (BindWidget))
	class UCUserWidget_CrossHair* CrossHair;

	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* Status;

	UPROPERTY(meta = (BindWidget))
	UCUserWidget_BaseProgressBar* HealthBar;

	UPROPERTY(meta = (BindWidget))
	UCUserWidget_BaseProgressBar* ManaBar;

	UPROPERTY(meta = (BindWidget))
	UCUserWidget_BaseProgressBar* StaminaBar;

	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* SlotFrame;

	UPROPERTY(meta = (BindWidget))
	class UCUserWidget_Slots* Slots;

	// 변경된 Stamina 값을 Update
	UFUNCTION()
	void UpdateStamina(float& InStamina, float& InMaxStamina);

	// 변경된 Health 값을 Update
	UFUNCTION()
	void UpdateHealth(float& InValue, float& InMaxValue);

	// 변경된 Mana 값을 Update
	UFUNCTION()
	void UpdateMana(float& InMana, float& InMaxMana);

	// Slots 변경
	UFUNCTION()
	void UpdateSlot(UTexture2D* InWeaponIcon, TArray<ACAbility*> InAbilities, bool InIsDefault);

	// Ability Activated
	UFUNCTION()
	void OnAbilityActivated(ACAbility* InAbility);

};
