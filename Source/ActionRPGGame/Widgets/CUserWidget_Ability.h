#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CUserWidget_Ability.generated.h"

// 전방 선언
class UOverlay;
class UImage;
class UProgressBar;

UCLASS()
class ACTIONRPGGAME_API UCUserWidget_Ability : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	UOverlay* Overlay;

	UPROPERTY(meta = (BindWidget))
	UImage* Frame;

	UPROPERTY(meta = (BindWidget))
	UImage* Background;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* Ability1;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* Ability2;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* Ability3;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* Ability4;
	
};
