#pragma once

#include "CoreMinimal.h"

// 무기 타입
UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	Dual, Bow, Throw, Max
};

// 몽타주 타입
UENUM(BlueprintType)
enum class EMontageType : uint8
{
	DoubleJump, EvadeForward, EvadeBack, EvadeLeft, EvadeRight, Max
};

// Model Type
UENUM(BlueprintType)
enum class EModelType : uint8
{
	GhostLady, Max
};

// Status Type
UENUM(BlueprintType)
enum class EStatusType : uint8
{
	Player, Monster, Max
};

// 캐릭터의 스피드 타입
UENUM(BlueprintType)
enum class ESpeedType : uint8
{
	Walk, Run, Max
};

// 캐릭터의 상태 타입
UENUM(BlueprintType)
enum class EStateType : uint8
{
	Idle, Crouch, Jump, DoubleJump, Evade, Max
};


