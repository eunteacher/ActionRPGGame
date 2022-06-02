#pragma once

#include "CoreMinimal.h"
#include "Weapon/CWeapon_Base.h"
#include "CTypes.generated.h"

// BaseCharacter 클래스에서 사용
// 소유하고 있는 웨폰에 대한 데이터
USTRUCT(BlueprintType)
struct FOwningWeapon
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
