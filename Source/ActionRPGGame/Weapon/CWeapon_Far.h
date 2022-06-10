#pragma once

#include "CoreMinimal.h"
#include "Weapon/CWeapon_Base.h"
#include "CWeapon_Far.generated.h"

// 전방 선언
class ACBaseCharacter;
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class ACTIONRPGGAME_API ACWeapon_Far : public ACWeapon_Base
{
	GENERATED_BODY()
public:
	// 생성자
	ACWeapon_Far();
	// Tick
	virtual void Tick(float DeltaSeconds) override;

	// 공격 함수
	virtual void OnAttack() override;

	// 공격이 모두 종료되면 호출
	virtual void OnReset() override;

	// 에임 실행 함수
	virtual void OnAim() override;

	// 에임 해제 실행 함수
	virtual void OffAim() override;

	// IsOverDraw Getter Setter
	bool GetIsOverDraw();
	void SetIsOverDraw(bool InIsOverDraw);
protected:
	// BeginPlay
	virtual void BeginPlay() override;

	// Aim 상태일 경우 Target을 Trace를 통해 찾는다.
	bool TargetTrace();

	
	// Weapon의 OwnerCharacter의 SpringArm
	USpringArmComponent* OwnerSpringArm;

	// Weapon의 OwnerCharacter의 Camera
	UCameraComponent* OwnerCamera;

	UPROPERTY(VisibleDefaultsOnly, Category = "ProjectileClass")
	TSubclassOf<class ACProjectile> ProjectileClass;

	// 에임 상태라면 true, 아니라면 false
	bool IsAiming;
	// OverDraw 상태라면 true, 아니라면 false
	bool IsOverDraw;
};
