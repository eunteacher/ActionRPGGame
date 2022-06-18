#pragma once

#include "CoreMinimal.h"
#include "Types/CEnumTypes.h"
#include "Engine/DataTable.h"
#include "NiagaraSystem.h"
#include "MatineeCameraShake.h"
#include "CDataTableType.generated.h"

// Character의 Ability 데이터 테이블
USTRUCT()
struct FOwningAbilityData : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category = "Weapon")
	EAbilityType Type;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	TSubclassOf<class ACAbility> AbilityClass;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	bool bOwning;
};

// Character의 Weapon 데이터 테이블
USTRUCT()
struct FOwningWeaponData : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category = "Weapon")
	EWeaponType Type;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	TSubclassOf<class ACWeapon> WeaponClass;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	bool bOwning;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	FName WeaponSocketName;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	FName WeaponHolsterSocketName;

};

// Weapon 클래스에서 사용될 무기 데이터 테이블
USTRUCT()
struct FWeaponData : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category = "Type")
	EAttackType AttackType;

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

// 사용할 모든 몽타주 데이터 테이블
USTRUCT(BlueprintType)
struct FMontageData : public FTableRowBase
{
	GENERATED_BODY()

public:
	// 모델 타입
	UPROPERTY(EditAnywhere, Category = "Type")
	EModelType ModelType;

	// 몽타주 타입
	UPROPERTY(EditAnywhere, Category = "Type")
	EMontageType MontageType;

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

// 사용할 모든 Sound 데이터 테이블
USTRUCT(BlueprintType)
struct FSoundData : public FTableRowBase
{
	GENERATED_BODY()

public:
	// Character Model Type
	UPROPERTY(EditAnywhere, Category = "Type")
	EModelType Type;
	// 점프
	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundBase* Jump;
	// 착지
	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundBase* Land;
	// 피하기
	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundBase* Evade;
	// 전투
	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundBase* Attack;

	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundBase* Hit;

	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundBase* Dead;

};

// Player와 Enemy의 Status 데이터 테이블
USTRUCT(BlueprintType)
struct FStatusData : public FTableRowBase
{
	GENERATED_BODY()

public:
	// StatusType
	UPROPERTY(EditAnywhere, Category = "Type")
	EStatusType Type;

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

};

// 발자국에 관련된 소리와 파티클 데이터 테이블
USTRUCT(BlueprintType)
struct FFootStepSoundData : public FTableRowBase
{
	GENERATED_BODY()
public:
	// 표면 
	UPROPERTY(EditAnywhere, Category = "Type")
	TEnumAsByte<EPhysicalSurface> Type;
	// 걷기 사운드
	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundBase* WalkSound;
	// 뛰기 사운드
	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundBase* RunSound;
	// Effect
	UPROPERTY(EditAnywhere, Category = "Effect")
	UNiagaraSystem* HitNiagaraEffect;
};
