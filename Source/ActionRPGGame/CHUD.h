#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CHUD.generated.h"

// 전방 선언
class UCUserWidget_HUD;

UCLASS()
class ACTIONRPGGAME_API ACHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	ACHUD();

	// TODO : 델리게이트로 변경해도 될듯 ?
	// PlayerController에 Status Value 값이 변경됨을 알리는 함수들
	void NotifyStamina(float InValue, float InMaxValue);
	void NotifyHealth(float InValue, float InMaxValue);
	void NotifyMana(float InValue, float InMaxValue);
	
	UPROPERTY(EditAnywhere, Category = "UserWidget")
	TSubclassOf<UCUserWidget_HUD> UserWidgetHUDClass;

	UPROPERTY()
	UCUserWidget_HUD* UserWidgetHUD;
	
protected:
	virtual void BeginPlay() override;

};
