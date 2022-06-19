#pragma once

#include "CoreMinimal.h"
#include "Abilities/CAbility.h"
#include "CAbility_TakeDown.generated.h"

UCLASS()
class ACTIONRPGGAME_API ACAbility_TakeDown : public ACAbility
{
	GENERATED_BODY()
public:
	ACAbility_TakeDown();

	virtual void Tick(float DeltaSeconds) override;

	virtual void OnActivation() override;
	virtual void OnProgress() override;
	virtual void OnDeActivation() override;

	
};
