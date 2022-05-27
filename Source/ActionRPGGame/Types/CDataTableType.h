#pragma once

#include "CoreMinimal.h"
#include "Types/CEnumTypes.h"
#include "Engine/DataTable.h"
#include "NiagaraSystem.h"
#include "CDataTableType.generated.h"

// Character SoundDataTable
USTRUCT(BlueprintType)
struct FSoundData : public FTableRowBase
{
	GENERATED_BODY()

public:
	// Character Model Type
	UPROPERTY(EditAnywhere)
	EModelType Type;
	// 점프
	UPROPERTY(EditAnywhere)
	USoundBase* Jump;
	// 착지
	UPROPERTY(EditAnywhere)
	USoundBase* Land;
	// 높은 착지
	UPROPERTY(EditAnywhere)
	USoundBase* HeavyLand;
	// 피하기
	UPROPERTY(EditAnywhere)
	USoundBase* Evade;
	// 전투
	UPROPERTY(EditAnywhere)
	USoundBase* Battle;
	// 어빌리티 1
	UPROPERTY(EditAnywhere)
	USoundBase* Ability1;
	// 어빌리티 2
	UPROPERTY(EditAnywhere)
	USoundBase* Ability2;
	// 어빌리티 3
	UPROPERTY(EditAnywhere)
	USoundBase* Ability3;
	// 어빌리티 4
	UPROPERTY(EditAnywhere)
	USoundBase* Ability4;
};

// MontageTable
USTRUCT(BlueprintType)
struct FMontageData : public FTableRowBase
{
	GENERATED_BODY()

public:
	// 몽타주 타입
	UPROPERTY(EditAnywhere)
	EMontageType Type;
	// 몽타주
	UPROPERTY(EditAnywhere)
	UAnimMontage* AnimMontage;
	// PlayRatio
	UPROPERTY(EditAnywhere)
	float PlayRatio = 1.0f;
	// 몽타주 시작 지점
	UPROPERTY(EditAnywhere)
	FName StartSection;
	// Effect
	UPROPERTY(EditAnywhere)
	UParticleSystem* Particle = nullptr;
	// Effect
	UPROPERTY(EditAnywhere)
	UNiagaraSystem* HitNiagaraEffect = nullptr;
	// 소켓 이름
	UPROPERTY(EditAnywhere)
	FName SocketName;

};

// Character StatusTable
USTRUCT(BlueprintType)
struct FStatusData : public FTableRowBase
{
	GENERATED_BODY()

public:
	// StatusType
	UPROPERTY(EditAnywhere)
	EStatusType Type;

	UPROPERTY(EditAnywhere)
	float Health;

	UPROPERTY(EditAnywhere)
	float MaxHealth;

	UPROPERTY(EditAnywhere)
	float Mana;

	UPROPERTY(EditAnywhere)
	float MaxMana;

	UPROPERTY(EditAnywhere)
	float Stamina;

	UPROPERTY(EditAnywhere)
	float MaxStamina;
};

// FootStep TableData 
USTRUCT(BlueprintType)
struct FFootStepSoundData : public FTableRowBase
{
	GENERATED_BODY()

public:
	// 표면 
	UPROPERTY(EditAnywhere)
	TEnumAsByte<EPhysicalSurface> Type;
	// 걷기 사운드
	UPROPERTY(EditAnywhere)
	USoundBase* WalkSound;
	// 뛰기 사운드
	UPROPERTY(EditAnywhere)
	USoundBase* RunSound;
};