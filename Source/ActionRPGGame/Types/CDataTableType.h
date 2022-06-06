#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "NiagaraSystem.h"
#include "MatineeCameraShake.h"
#include "CDataTableType.generated.h"

// 전방 선언
class ACWeapon_Base;
enum class EStatusType : uint8;
enum class EModelType : uint8;
enum class EMontageType : uint8;
enum class EAttackType : uint8;
enum class EWeaponType : uint8;

// Character의 Weapon 데이터 테이블
USTRUCT()
struct FOwningWeaponData : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category = "Weapon")
	EWeaponType Type;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	TSubclassOf<ACWeapon_Base> WeaponClass;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	bool bOwning;

	UPROPERTY(EditAnywhere, Category = "Socket")
	FName WeaponSocketName;

	UPROPERTY(EditAnywhere, Category = "Socket")
	FName WeaponHolsterSocketName;
};

// Weapon 클래스에서 사용될 무기 데이터 테이블
USTRUCT()
struct FWeaponData : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category = "Type")
	TMap<EAttackType, EMontageType> Type;

	UPROPERTY(EditAnywhere, Category = "Value")
	float Damage;

	UPROPERTY(EditAnywhere, Category = "Value")
	float LaunchValue;

	UPROPERTY(EditAnywhere, Category = "Value")
	float HitStopTime;
	
	UPROPERTY(EditAnywhere, Category = "Effect")
	UParticleSystem* HitParticle = nullptr;

	UPROPERTY(EditAnywhere, Category = "CameraShake")
	TSubclassOf<UMatineeCameraShake> ShakeClass;
};

// MontageComponent에서 사용, 사용할 모든 몽타주 데이터 테이블
USTRUCT(BlueprintType)
struct FMontageData : public FTableRowBase
{
	GENERATED_BODY()

public:
	// 몽타주 타입
	UPROPERTY(EditAnywhere, Category = "Type")
	EMontageType Type;
	// 몽타주
	UPROPERTY(EditAnywhere, Category = "Montage")
	TMap<EModelType, UAnimMontage*> AnimMontageMaps;
	// PlayRatio
	UPROPERTY(EditAnywhere, Category = "Montage")
	float PlayRatio = 1.0f;
	// 몽타주 시작 지점
	UPROPERTY(EditAnywhere, Category = "Montage")
	FName StartSection;
	// ParticleSystem
	UPROPERTY(EditAnywhere, Category = "Effect")
	UParticleSystem* Particle = nullptr;
	// NiagaraSystem Effect
	UPROPERTY(EditAnywhere, Category = "Effect")
	UNiagaraSystem* HitNiagaraEffect = nullptr;
	// 소켓 이름
	UPROPERTY(EditAnywhere, Category= "Socket")
	FName SocketName;

};

// SoundComponent에서 사용, 사용한 모든 Sound 데이터 테이블
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
	// 높은 착지
	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundBase* Equip;
	// 피하기
	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundBase* Evade;
	// 전투
	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundBase* Attack;
	// 어빌리티 1
	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundBase* Ability1;
	// 어빌리티 2
	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundBase* Ability2;
	// 어빌리티 3
	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundBase* Ability3;
	// 어빌리티 4
	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundBase* Ability4;
};

// Character 클래스에서 사용, Player와 Monster의 Status 데이터 테이블
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

// FootStepComponent에서 사용, 발자국에 관련된 소리와 파티클 데이터 테이블
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
	UNiagaraSystem* HitNiagaraEffect = nullptr;
};
