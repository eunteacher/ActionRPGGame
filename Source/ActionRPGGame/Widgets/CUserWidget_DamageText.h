#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CUserWidget_DamageText.generated.h"

UCLASS()
class ACTIONRPGGAME_API UCUserWidget_DamageText : public UUserWidget
{
	GENERATED_BODY()
public:
	void SetDamageText(FText InText, bool IsPlayer);
	
protected:
	UPROPERTY(meta = (BindWidget))
	class UOverlay* Overlay;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* DamageText;

};
