#pragma once

#include "CoreMinimal.h"
#include "Abilities/CAbility.h"
#include "CAbility_ExplosionArrow.generated.h"

UCLASS()
class ACTIONRPGGAME_API ACAbility_ExplosionArrow : public ACAbility
{
	GENERATED_BODY()
public:
	ACAbility_ExplosionArrow();

	virtual void OnActivation() override;
	virtual void OnProgress() override;
	virtual void OnDeActivation() override;

	
};
