#pragma once

#include "CoreMinimal.h"
#include "Components/CFootStepSoundComponent.h"
#include "GameFramework/Actor.h"
#include "CBurningEffect.generated.h"

class ACBaseCharacter;
class ACAbility;
UCLASS()
class ACTIONRPGGAME_API ACBurningEffect : public AActor
{
	GENERATED_BODY()
	
public:	
	ACBurningEffect();

	virtual void Tick(float DeltaTime) override;

	void InitBurningEffect(ACBaseCharacter* InHitCharacter, ACAbility* InOwnerAbility);

	void SetHitCharacter(ACBaseCharacter* InHitCharacter);


protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void BurningDamage();

	UNiagaraComponent* NiagaraComponent;

	UPROPERTY(VisibleDefaultsOnly, Category = "Effect")
	class UNiagaraSystem* BurningEffect;

	UPROPERTY()
	ACBaseCharacter* HitCharacter;

	UPROPERTY(EditAnywhere, Category= "Value")
	float Damage;

	bool IsTimer;

	UPROPERTY()
	ACAbility* OwnerAbility;
	
};
