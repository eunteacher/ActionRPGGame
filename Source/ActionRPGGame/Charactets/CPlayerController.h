#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameFramework/PlayerController.h"
#include "CPlayerController.generated.h"

// 델리 게이트 
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FHealthChanged, float&, InValue, float&, InMaxValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FManaChanged, float&, InValue, float&, InMaxValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FStaminaChanged, float&, InValue, float&, InMaxValue);

// 전방 선언
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

	UPROPERTY(VisibleDefaultsOnly, Category = "UserWidget")
	TSubclassOf<UCUserWidget_HUD> UserWidgetHUDClass; // UserWidgetHUD 클래스

protected:
	// Begin Play
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	UCUserWidget_HUD* UserWidgetHUD; // UserWidgetHUD
};
