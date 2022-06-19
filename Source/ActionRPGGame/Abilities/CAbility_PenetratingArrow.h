#pragma once

#include "CoreMinimal.h"
#include "Abilities/CAbility.h"
#include "CAbility_PenetratingArrow.generated.h"

UCLASS()
class ACTIONRPGGAME_API ACAbility_PenetratingArrow : public ACAbility
{
	GENERATED_BODY()
public:
	ACAbility_PenetratingArrow();

	virtual void Tick(float DeltaSeconds) override;

	virtual void OnActivation() override;
	virtual void OnProgress() override;
	virtual void OnDeActivation() override;

	
};
