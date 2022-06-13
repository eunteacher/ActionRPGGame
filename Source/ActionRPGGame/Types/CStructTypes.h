#pragma once

#include "CoreMinimal.h"
#include "CDataTableType.h"
#include "MatineeCameraShake.h"
#include "NiagaraSystem.h"
#include "CStructTypes.generated.h"

// 전방 선언
enum class EMontageType : uint8;
class ACWeapon_Base;
class ACProjectile;

USTRUCT(BlueprintType)
struct FUseStatusData
{
	GENERATED_BODY()

public:
	FUseStatusData(): Health(1.0f), MaxHealth(1.0f), Mana(1.0f), MaxMana(1.0f), Stamina(1.0f), MaxStamina(1.0f)
	{
	}

	FUseStatusData(float& InHealth, float& InMaxHealth, float& InMana, float& InMaxMana, float& InStamina, float& InMaxStamina)
		: Health(InHealth), MaxHealth(InMaxHealth), Mana(InMana), MaxMana(InMaxMana), Stamina(InStamina), MaxStamina(InMaxStamina)
	{
		
	}

	UPROPERTY(EditAnywhere, Category = "Status")
	float Health;

	UPROPERTY(EditAnywhere, Category = "Status")
	float MaxHealth;

	UPROPERTY(EditAnywhere, Category = "Status")
	float Mana;

	UPROPERTY(EditAnywhere, Category = "Status")
	float MaxMana;

	UPROPERTY(EditAnywhere, Category = "Status")
	float Stamina;

	UPROPERTY(EditAnywhere, Category = "Status")
	float MaxStamina;

	FUseStatusData operator=(const FStatusData* InData)
	{
		this->Health = InData->Health;
		this->MaxHealth = InData->MaxHealth;
		this->Mana = InData->Mana;
		this->MaxMana = InData->MaxMana;
		this->Stamina = InData->Stamina;
		this->MaxStamina = InData->MaxStamina;
		
		return FUseStatusData(Health,MaxHealth,Mana,MaxMana,Stamina,MaxStamina);
	}
};

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
	
	UPROPERTY(EditAnywhere, Category = "HitType")
	EMontageType HitMontageType;

	UPROPERTY(EditAnywhere, Category = "Effect")
	UNiagaraSystem* HitNiagaraEffect;

	UPROPERTY(EditAnywhere, Category = "CameraShake")
	TSubclassOf<UMatineeCameraShake> ShakeClass;
};

USTRUCT(BlueprintType)
struct FUseMontageData
{
	GENERATED_BODY()
public:
	FUseMontageData(): AnimMontage(nullptr), PlayRatio(1.0f), StartSection("None")
	{
	}

	// 몽타주
	UPROPERTY(EditAnywhere, Category = "Montage")
	UAnimMontage* AnimMontage;

	// PlayRatio
	UPROPERTY(EditAnywhere, Category = "Montage")
	float PlayRatio;

	// 몽타주 시작 지점
	UPROPERTY(EditAnywhere, Category = "Montage")
	FName StartSection;
};

USTRUCT(BlueprintType)
struct FWeaponIconInfo
{
	GENERATED_BODY()

public:
	FWeaponIconInfo(): WeaponIcon(nullptr), Ability1_Icon(nullptr), Ability2_Icon(nullptr), Ability3_Icon(nullptr), Ability4_Icon(nullptr)
	{
		
	}

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
	FEquipedWeaponData(): Weapon(nullptr), IsAiming(false), WeaponSocketName("None"), WeaponHolsterSocketName("None")
	{
		
	}

	FEquipedWeaponData(const FOwningWeaponData* InData, ACWeapon_Base* InWeapon)
	{
		this->Weapon = InWeapon;
		this->WeaponSocketName = InData->WeaponSocketName;
		this->WeaponHolsterSocketName = InData->WeaponHolsterSocketName;

		this->WeaponIconInfo.WeaponIcon = InData->WeaponIcon;
		this->WeaponIconInfo.Ability1_Icon = InData->Ability1_Icon;
		this->WeaponIconInfo.Ability2_Icon = InData->Ability2_Icon;
		this->WeaponIconInfo.Ability3_Icon = InData->Ability3_Icon;
		this->WeaponIconInfo.Ability4_Icon = InData->Ability4_Icon;

		this->IsAiming = false;
	}
	
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
