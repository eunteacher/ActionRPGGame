#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CDamageText.generated.h"

class UWidgetComponent;
UCLASS()
class ACTIONRPGGAME_API ACDamageText : public AActor
{
	GENERATED_BODY()
	
public:
	// 생성자
	ACDamageText();
	// Tick
	virtual void Tick(float DeltaTime) override;

	void SetDamageText(FText InText, bool InIsPlayer, bool InIsDamageEffect = false);
protected:
	// BeginPlay
	virtual void BeginPlay() override;

	// Scene 컴포넌트, 루트 컴포넌트
	UPROPERTY(VisibleDefaultsOnly, Category = "Component")
	USceneComponent* Root;

	UPROPERTY(VisibleDefaultsOnly,Category = "Component")
	UWidgetComponent* DamageTextWidget;

};
