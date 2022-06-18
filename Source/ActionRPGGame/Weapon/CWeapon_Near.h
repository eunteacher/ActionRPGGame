#pragma once

#include "CoreMinimal.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Weapon/CWeapon.h"
#include "CWeapon_Near.generated.h"

// 전방 선언
class UCapsuleComponent;

/*
 * 근접 무기 클래스
 * 콤보 공격과 충돌체 On/Off
 */
UCLASS()
class ACTIONRPGGAME_API ACWeapon_Near : public ACWeapon
{
	GENERATED_BODY()

public:
	// 생성자
	ACWeapon_Near();

	virtual void Tick(float DeltaSeconds) override;
	
	// 공격 실행 함수
	virtual void OnAttack() override;
	// 공격이 모두 종료되면 호출
	virtual void OnReset() override;
	
	// Combo 공격 실행
	void ComboAttack();

	UPROPERTY(EditAnywhere, Category = "Trace")
	TEnumAsByte<EDrawDebugTrace::Type> DrawDebugType;

	UPROPERTY(EditAnywhere, Category = "Trace")
	TEnumAsByte<ETraceTypeQuery> TraceType;

protected:
	// BeginPlay()
	virtual void BeginPlay() override;

	// 충돌 검사
	void OnSphereTrace();

	void LaunchAttacker();
	
	// StaticMesh 컴포넌트, 무기의 Mesh
	UPROPERTY(VisibleDefaultsOnly, Category = "Component")
	UStaticMeshComponent* WeaponStaticMesh;
	
	// 콤보 공격 여부
	bool CanCombo;

	// 이미 공격받은 Actors
	UPROPERTY()
	TArray<AActor*> HittedActors;

};
