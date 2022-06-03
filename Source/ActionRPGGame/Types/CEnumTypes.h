#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EAttackType : uint8
{
	Sword_Combo1,
	Sword_Combo2,
	Sword_Combo3,
	Bow_Attack,
	Max
};

// 무기 타입
UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	Default,
	Sword,
	Bow,
	Max
};

// 몽타주 타입
UENUM(BlueprintType)
enum class EMontageType : uint8
{
	EvadeForward,
	EvadeBack,
	EvadeLeft,
	EvadeRight,
	Equip_Sword,
	Equip_Bow,
	UnEquip_Sword,
	UnEquip_Bow,
	Sword_Combo1,
	Sword_Combo2,
	Sword_Combo3,
	Max
};

// Model Type
UENUM(BlueprintType)
enum class EModelType : uint8
{
	GhostLady,
	Max
};

// Status Type
UENUM(BlueprintType)
enum class EStatusType : uint8
{
	Player,
	Monster,
	Max
};

// 캐릭터의 스피드 타입
UENUM(BlueprintType)
enum class ESpeedType : uint8
{
	Walk,
	Run,
	Max
};

// 캐릭터의 상태 타입
UENUM(BlueprintType)
enum class EStateType : uint8
{
	Idle_Walk_Run,
	Jump,
	Evade,
	Equip,
	UnEquip,
	Attack,
	Max
};
