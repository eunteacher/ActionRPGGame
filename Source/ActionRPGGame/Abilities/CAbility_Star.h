#pragma once

#include "CoreMinimal.h"
#include "Abilities/CAbility.h"
#include "CAbility_Star.generated.h"

UCLASS()
class ACTIONRPGGAME_API ACAbility_Star : public ACAbility
{
	GENERATED_BODY()

public:
	ACAbility_Star();

	virtual void Tick(float DeltaSeconds) override;

	virtual void OnActivation() override;
	virtual void OnProgress() override;
	virtual void OnDeActivation() override;

	
};
