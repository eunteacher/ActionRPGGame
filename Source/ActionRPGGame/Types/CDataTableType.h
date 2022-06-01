#pragma once

#include "CoreMinimal.h"
#include "Types/CEnumTypes.h"
#include "Engine/DataTable.h"
#include "NiagaraSystem.h"
#include "MatineeCameraShake.h"
#include "CDataTableType.generated.h"

USTRUCT()
struct FWeaponData : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category = "Type")
	EWeaponType Type;

	UPROPERTY(EditAnywhere, Category = "Value")
	int32 ComboCount;

	UPROPERTY(EditAnywhere, Category = "Value")
	float Damage;

	UPROPERTY(EditAnywhere, Category = "Value")
	float LaunchValue;

	UPROPERTY(EditAnywhere, Category = "Value")
	float HitStopTime;
	
	UPROPERTY(EditAnywhere, Category = "Effect")
	UParticleSystem* HitParticle = nullptr;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UMatineeCameraShake> ShakeClass;
};

// MontageTable
USTRUCT(BlueprintType)
struct FMontageData : public FTableRowBase
{
	GENERATED_BODY()

public:
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
	// Effect
	UPROPERTY(EditAnywhere, Category = "Effect")
	UParticleSystem* Particle = nullptr;
	// Effect
	UPROPERTY(EditAnywhere, Category = "Effect")
	UNiagaraSystem* HitNiagaraEffect = nullptr;
	// 소켓 이름
	UPROPERTY(EditAnywhere, Category= "Socket")
	FName SocketName;
	// 해당하는 몽타주의 모델 타입
	UPROPERTY(EditAnywhere, Category = "Type")
	EModelType ModelType;
};

// Character SoundDataTable
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
	USoundBase* HeavyLand;
	// 피하기
	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundBase* Evade;
	// 전투
	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundBase* Battle;
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

// Character StatusTable
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

// FootStep TableData 
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
};
