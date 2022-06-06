#pragma once

#include "CoreMinimal.h"
#include "CStructTypes.generated.h"

// 전방 선언
class ACWeapon_Base;

USTRUCT(BlueprintType)
struct FEquipedWeaponData
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category = "Weapon")
	ACWeapon_Base* Weapon;
	
	UPROPERTY(EditAnywhere, Category = "Socket")
	FName WeaponSocketName;

	UPROPERTY(EditAnywhere, Category = "Socket")
	FName WeaponHolsterSocketName;
};
