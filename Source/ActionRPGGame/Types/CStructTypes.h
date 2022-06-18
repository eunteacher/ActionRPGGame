#pragma once

#include "CoreMinimal.h"
#include "CDataTableType.h"
#include "MatineeCameraShake.h"
#include "NiagaraSystem.h"
#include "CStructTypes.generated.h"

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
struct FEquipAbilityData
{
	GENERATED_BODY()
public:
	FEquipAbilityData(): Ability(nullptr)
	{
	}
	
	UPROPERTY(EditAnywhere, Category = "Ability")
	ACAbility* Ability;
};

USTRUCT(BlueprintType)
struct FEquipWeaponData
{
	GENERATED_BODY()
public:
	FEquipWeaponData(): Weapon(nullptr), IsAiming(false), WeaponSocketName("None"), WeaponHolsterSocketName("None")
	{
		
	}

	UPROPERTY(EditAnywhere, Category = "Weapon")
	ACWeapon* Weapon;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	bool IsAiming;
	
	UPROPERTY(EditAnywhere, Category = "SocketName")
	FName WeaponSocketName;

	UPROPERTY(EditAnywhere, Category = "SocketName")
	FName WeaponHolsterSocketName;
};

