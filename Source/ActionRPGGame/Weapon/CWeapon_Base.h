#pragma once

#include "CoreMinimal.h"
#include "Types/CEnumTypes.h"
#include "Types/CDataTableType.h"
#include "Engine/DataTable.h"
#include "GameFramework/Actor.h"
#include "Types/CStructTypes.h"
#include "CWeapon_Base.generated.h"

UCLASS()
class ACTIONRPGGAME_API ACWeapon_Base : public AActor
{
	GENERATED_BODY()
	
public:
	// 생성자	
	ACWeapon_Base();
	virtual void Tick(float DeltaSeconds) override;

	// 무기 장착 몽타주 실행 및 무기 장착 여부 설정
	void OnEquip();

	// 무기 해제 몽타주 실행 및 무기 장착 여부 설정
	void OnUnEquip();

	// 무기를 캐릭터에 Attach, AnimNotify를 통해 호출
	void OnAttach(FName InSocketName);

	// 공격 실행
	virtual void OnAttack();

	// 공격이 종료되고, 사용한 변수들을 초기화하는 함수
	virtual void OnReset();

	// Aim 실행 함수
	virtual void OnAim();

	// OffAim 실행 함수 
	virtual void OffAim();

	// OnFire 함수, Projectile을 스폰하고 발사한다.
	virtual void OnFire();
	
protected:
	// BeginPlay
	virtual void BeginPlay() override;
	
	// Scene 컴포넌트, 루트 컴포넌트
	UPROPERTY(VisibleDefaultsOnly, Category = "Component")
	USceneComponent* Root;

	// Weapon Type
	UPROPERTY(VisibleDefaultsOnly, Category = "Type")
	EWeaponType Weapon;

	// WeaponDataTable
	UPROPERTY(VisibleDefaultsOnly, Category = "DataTable")
	UDataTable* WeaponTable;

	// Attack Type, 공격의 Type
	UPROPERTY(VisibleDefaultsOnly, Category="Type")
	EAttackType AttackType;

	// 사용할 Weapon Data
	TMap<EAttackType, FUseWeaponData> UseWeaponDataMaps;

	bool IsEquip; // 무기 장착 유무
	bool IsAttack; // 공격 실행 여부
};
