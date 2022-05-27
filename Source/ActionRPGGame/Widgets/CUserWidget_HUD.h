#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CUserWidget_HUD.generated.h"

// 전방 선언
class UCanvasPanel;
class UCUserWidget_BaseProgressBar;

UCLASS()
class ACTIONRPGGAME_API UCUserWidget_HUD : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void UpdateStamina(float InStamina, float InMaxStamina);

	UFUNCTION()
	void UpdateHealth(float InHealth, float InMaxHealth);

	UFUNCTION()
	void UpdateMana(float InMana, float InMaxMana);

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
	UCanvasPanel* AbilityFrame;

	UPROPERTY(meta = (BindWidget))
	class UCUserWidget_Ability* Ability;
};
