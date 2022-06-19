#pragma once

#include "CoreMinimal.h"
#include "CAbility.h"
#include "CAbility_FireSword.generated.h"

class UNiagaraSystem;

UCLASS()
class ACTIONRPGGAME_API ACAbility_FireSword : public ACAbility
{
	GENERATED_BODY()
public:
	// 생성자
	ACAbility_FireSword();

	virtual void Tick(float DeltaSeconds) override;

	virtual void OnActivation() override;
	virtual void OnProgress() override;
	virtual void OnDeActivation() override;

	void OnSphereTrace();
	
protected:
	UPROPERTY(VisibleDefaultsOnly, Category = "Effect")
	UNiagaraSystem* FireEffect;

	UPROPERTY(VisibleDefaultsOnly, Category = "Effect")
	UNiagaraSystem* AuraEffect;

	UPROPERTY(EditAnywhere, Category = "UserSetting")
	FName AttachSocketName;

	UPROPERTY(EditAnywhere, Category = "UserSetting")
	TSubclassOf<class ACBurningEffect> BurningEffectClass;

	// 이미 공격받은 Actors
	UPROPERTY()
	TArray<AActor*> HittedActors;

	float OriginalDamage;
};
