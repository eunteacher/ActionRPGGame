#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameFramework/PlayerController.h"
#include "CPlayerController.generated.h"

// 전방 선언
class UCUserWidget_HUD;

UCLASS()
class ACTIONRPGGAME_API ACPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ACPlayerController();

	// Tick
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, Category = "UserWidget")
	TSubclassOf<UCUserWidget_HUD> UserWidgetHUDClass; // UserWidgetHUD 클래스

	UFUNCTION()
	void UpdateHealth(float InHealth, float InMaxHealth);

	UFUNCTION()
	void UpdateMana(float InMana, float InMaxMana);

	UFUNCTION()
	void UpdateStamina(float InStamina, float InMaxStamina);

protected:
	// Begin Play
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	UCUserWidget_HUD* UserWidgetHUD; // UserWidgetHUD
};
