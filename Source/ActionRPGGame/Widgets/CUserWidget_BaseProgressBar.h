#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "CUserWidget_BaseProgressBar.generated.h"

UCLASS()
class ACTIONRPGGAME_API UCUserWidget_BaseProgressBar : public UUserWidget
{
	GENERATED_BODY()

public:
	// ProgressBar 업데이트 함수
	UFUNCTION()
	void UpdateValue(float InValue, float InMaxValue);

protected:
	UPROPERTY(meta = (BindWidget))
	class UOverlay* Overlay;

	UPROPERTY(meta = (BindWidget))
	class UImage* Frame;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* ProgressBar;
	
};
