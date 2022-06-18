#pragma once

#include "CoreMinimal.h"
#include "CAbility.h"
#include "Kismet/KismetSystemLibrary.h"
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
	virtual void OnDeActivation() override;
	virtual void OnNotify() override;

	void OnSphereTrace();

	UPROPERTY(EditAnywhere, Category = "Trace")
	TEnumAsByte<EDrawDebugTrace::Type> DrawDebugType;

	UPROPERTY(EditAnywhere, Category = "Trace")
	TEnumAsByte<ETraceTypeQuery> TraceType;
	
protected:
	UPROPERTY(VisibleDefaultsOnly, Category = "Effect")
	UNiagaraSystem* FireEffect;

	UPROPERTY(VisibleDefaultsOnly, Category = "Effect")
	UNiagaraSystem* AuraEffect;

	UPROPERTY(EditAnywhere, Category = "UserSetting")
	FName AttachSocketName;

	// 이미 공격받은 Actors
	UPROPERTY()
	TArray<AActor*> HittedActors;
};
