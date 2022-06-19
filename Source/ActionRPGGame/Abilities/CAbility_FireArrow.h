
#pragma once

#include "CoreMinimal.h"
#include "Abilities/CAbility.h"
#include "CAbility_FireArrow.generated.h"

UCLASS()
class ACTIONRPGGAME_API ACAbility_FireArrow : public ACAbility
{
	GENERATED_BODY()

public:
	ACAbility_FireArrow();

	virtual void Tick(float DeltaSeconds) override;

	virtual void OnActivation() override;
	virtual void OnProgress() override;
	virtual void OnDeActivation() override;

	
};
