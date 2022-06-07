#pragma once

#include "CoreMinimal.h"
#include "CStructTypes.generated.h"

// 전방 선언
class ACWeapon_Base;

USTRUCT(BlueprintType)
struct FWeaponIconInfo
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Icon")
	UTexture2D* WeaponIcon;

	UPROPERTY(EditAnywhere, Category = "Icon")
	UTexture2D* Ability1_Icon;

	UPROPERTY(EditAnywhere, Category = "Icon")
	UTexture2D* Ability2_Icon;

	UPROPERTY(EditAnywhere, Category = "Icon")
	UTexture2D* Ability3_Icon;

	UPROPERTY(EditAnywhere, Category = "Icon")
	UTexture2D* Ability4_Icon;
};

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

	UPROPERTY(EditAnywhere, Category = "Icon")
	FWeaponIconInfo WeaponIconInfo;
	
};
