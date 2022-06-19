// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/CAbility.h"
#include "CAbility_RainArrow.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONRPGGAME_API ACAbility_RainArrow : public ACAbility
{
	GENERATED_BODY()
public:
	ACAbility_RainArrow();

	virtual void Tick(float DeltaSeconds) override;

	virtual void OnActivation() override;
	virtual void OnProgress() override;
	virtual void OnDeActivation() override;

	
};
