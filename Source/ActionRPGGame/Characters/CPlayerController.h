#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Types/CStructTypes.h"
#include "CPlayerController.generated.h"

enum class ESlotType : uint8;
// 델리 게이트 
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FHealthChanged, float&, InValue, float&, InMaxValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FManaChanged, float&, InValue, float&, InMaxValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FStaminaChanged, float&, InValue, float&, InMaxValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FWeaponChanged, UTexture2D*, InWeaponIcon, TArray<ACAbility*>, InAbilities, bool, InIsDefault);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAbilityActivated, ACAbility*, InAbility);

class UCUserWidget_HUD;

UCLASS()
class ACTIONRPGGAME_API ACPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	// 생성자
	ACPlayerController();
	// Tick
	virtual void Tick(float DeltaSeconds) override;

	// 델리게이트
	UPROPERTY()
	FHealthChanged OnHealthChanged;

	UPROPERTY()
	FManaChanged OnManaChanged;

	UPROPERTY()
	FStaminaChanged OnStaminaChanged;

	UPROPERTY()
	FWeaponChanged OnWeaponChanged;

	UPROPERTY()
	FAbilityActivated OnAbilityActivated;

	UPROPERTY(VisibleDefaultsOnly, Category = "UserWidget")
	TSubclassOf<UCUserWidget_HUD> UserWidgetHUDClass; // UserWidgetHUD 클래스

protected:
	// Begin Play
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	UCUserWidget_HUD* UserWidgetHUD; // UserWidgetHUD
};
