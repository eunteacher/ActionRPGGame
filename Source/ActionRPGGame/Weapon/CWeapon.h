#pragma once

#include "CoreMinimal.h"
#include "Types/CEnumTypes.h"
#include "Engine/DataTable.h"
#include "GameFramework/Actor.h"
#include "Types/CStructTypes.h"
#include "CWeapon.generated.h"

// 전방 선언
class ACDamageText;
class ACAbility;

UCLASS()
class ACTIONRPGGAME_API ACWeapon : public AActor
{
	GENERATED_BODY()
	
public:
	// 생성자	
	ACWeapon();
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

	virtual void GetStaticMeshComponent(UStaticMeshComponent*& OutStaticMeshComponent);
	
	EMontageType GetHitMontageType() const;
	
	UTexture2D* GetWeaponIcon() { return WeaponIcon; }
protected:
	// BeginPlay
	virtual void BeginPlay() override;
	
	// Scene 컴포넌트, 루트 컴포넌트
	UPROPERTY(VisibleDefaultsOnly, Category = "Component")
	USceneComponent* Root;
	
	// Weapon Type
	UPROPERTY(VisibleDefaultsOnly, Category = "UserSetting")
	EWeaponType Weapon;

	// Attack Type, 공격의 Type
	UPROPERTY(VisibleDefaultsOnly, Category = "UserSetting")
	EAttackType AttackType;

	// WeaponDataTable
	UPROPERTY(VisibleDefaultsOnly, Category = "UserSetting")
	UDataTable* WeaponTable;

	UPROPERTY(VisibleDefaultsOnly, Category = "UserSetting")
	UTexture2D* WeaponIcon;
	
	UPROPERTY(VisibleDefaultsOnly, Category = "UserSetting")
	TSubclassOf<ACDamageText> DamageTextClass;

	UPROPERTY(VisibleDefaultsOnly, Category = "UserSetting")
	TArray<EAbilityType> OwningAbilities;
	
	// 사용할 Weapon Data, 공격 형태가 하나가 아닐 수 있기 때문에 TMap으로 구현
	UPROPERTY(VisibleDefaultsOnly, Category = "UserSetting")
	TMap<EAttackType, FUseWeaponData> UseWeaponDataMaps;

	bool IsEquip; // 무기 장착 유무
	bool IsAttack; // 공격 실행 여부
};
