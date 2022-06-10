#pragma once

#include "CoreMinimal.h"
#include "Weapon/CWeapon_Base.h"
#include "CWeapon_Near.generated.h"

// 전방 선언
class UCapsuleComponent;

/*
 * 근접 무기 클래스
 * 콤보 공격과 충돌체 On/Off
 */
UCLASS()
class ACTIONRPGGAME_API ACWeapon_Near : public ACWeapon_Base
{
	GENERATED_BODY()

public:
	// 생성자
	ACWeapon_Near();

	// 공격 실행 함수
	virtual void OnAttack() override;
	// 공격이 모두 종료되면 호출
	virtual void OnReset() override;
	
	// Combo 공격 실행
	void ComboAttack();

protected:
	// BeginPlay()
	virtual void BeginPlay() override;
	
	// 콤보 공격 여부
	bool CanCombo;

};
