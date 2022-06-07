#pragma once

#include "CoreMinimal.h"
#include "Weapon/CWeapon_Base.h"
#include "CWeapon_Far.generated.h"

UCLASS()
class ACTIONRPGGAME_API ACWeapon_Far : public ACWeapon_Base
{
	GENERATED_BODY()
public:
	ACWeapon_Far();

	virtual void OnAttack() override;
	// 공격이 모두 종료되면 호출
	virtual void OnReset() override;
	
};
