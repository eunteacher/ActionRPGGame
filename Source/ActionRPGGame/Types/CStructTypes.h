#pragma once

#include "CoreMinimal.h"
#include "MatineeCameraShake.h"
#include "NiagaraSystem.h"
#include "CStructTypes.generated.h"

// 전방 선언
enum class EMontageType : uint8;
class ACWeapon_Base;
class ACProjectile;

USTRUCT(BlueprintType)
struct FUseWeaponData
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category = "Type")
	EMontageType MontageType;

	UPROPERTY(EditAnywhere, Category = "Value")
	float Damage;

	UPROPERTY(EditAnywhere, Category = "Value")
	float LaunchValue;

	UPROPERTY(EditAnywhere, Category = "Value")
	float HitStopTime;
	
	UPROPERTY(EditAnywhere, Category = "Effect")
	UParticleSystem* HitParticle = nullptr;

	UPROPERTY(EditAnywhere, Category = "Effect")
	UNiagaraSystem* HitNiagaraEffect = nullptr;

	UPROPERTY(EditAnywhere, Category = "CameraShake")
	TSubclassOf<UMatineeCameraShake> ShakeClass;
};

USTRUCT(BlueprintType)
struct FUseMontageData
{
	GENERATED_BODY()
public:
	// 몽타주
	UPROPERTY(EditAnywhere, Category = "Montage")
	UAnimMontage* AnimMontage;

	// PlayRatio
	UPROPERTY(EditAnywhere, Category = "Montage")
	float PlayRatio = 1.0f;

	// 몽타주 시작 지점
	UPROPERTY(EditAnywhere, Category = "Montage")
	FName StartSection;
};

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

	UPROPERTY(EditAnywhere, Category = "Weapon")
	bool IsAiming;
	
	UPROPERTY(EditAnywhere, Category = "Socket")
	FName WeaponSocketName;

	UPROPERTY(EditAnywhere, Category = "Socket")
	FName WeaponHolsterSocketName;

	UPROPERTY(EditAnywhere, Category = "Icon")
	FWeaponIconInfo WeaponIconInfo;


};
