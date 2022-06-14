#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EPatrolType : uint8
{
	None,
	Line,
	Triangle,
	Square,
	Max	
};

UENUM(BlueprintType)
enum class EAttackType : uint8
{
	Near_Combo1,
	Near_Combo2,
	Near_Combo3,
	Far_OverDraw,
	Far_Fire,
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
	HitLight,
	HitHeavy,
	Hit_KnockBack,
	Bow_Fire,
	Bow_OverDraw,
	Dead,
	Max
};

// Model Type
UENUM(BlueprintType)
enum class EModelType : uint8
{
	GhostLady,
	Gruntling,
	Max
};

// Status Type
UENUM(BlueprintType)
enum class EStatusType : uint8
{
	Player,
	Enemy_Grunting,
	Enemy_Boss,
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
