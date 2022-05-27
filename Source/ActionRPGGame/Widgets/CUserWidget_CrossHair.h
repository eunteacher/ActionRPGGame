#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CUserWidget_CrossHair.generated.h"

UCLASS()
class ACTIONRPGGAME_API UCUserWidget_CrossHair : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* CanvasPanel;

	UPROPERTY(meta = (BindWidget))
	class USizeBox* CrossHairFrame;

	UPROPERTY(meta = (BindWidget))
	class UImage* CrossHair;
};
