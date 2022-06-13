#pragma once

#include "CoreMinimal.h"
#include "Weapon/CWeapon_Near.h"
#include "CWeapon_Near_Sword.generated.h"

/*
 * SttaticMesh와 Capsule을 생성 및 초기화
 * Weapon_Sword 데이터 테이블 저장
 * WeaponType 설정
 */
UCLASS()
class ACTIONRPGGAME_API ACWeapon_Near_Sword : public ACWeapon_Near
{
	GENERATED_BODY()
public:
	// 생성자
	ACWeapon_Near_Sword();

protected:
	// BeginPlay
	virtual void BeginPlay() override;

};
