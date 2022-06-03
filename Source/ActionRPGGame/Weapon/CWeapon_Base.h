#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameFramework/Actor.h"
#include "Types/CEnumTypes.h"
#include "CWeapon_Base.generated.h"

// 전방 선언
struct FWeaponData;
enum class EWeaponType : uint8;

UCLASS()
class ACTIONRPGGAME_API ACWeapon_Base : public AActor
{
	GENERATED_BODY()
	
public:
	// 생성자	
	ACWeapon_Base();

	// 무기 장착 몽타주 실행 및 무기 장착 여부 설정
	void OnEquip();
	// 무기 해제 몽타주 실행 및 무기 장착 여부 설정
	void OnUnEquip();
	// 무기를 캐릭터에 Attach, AnimNotify를 통해 호출
	void OnAttach(FName InSocketName);
	// Capsule 충돌 켜기, AnimNotifyState를 통해 호출
	virtual void OnCollision();
	// Capsule 충돌 끄기, AnimNotifyState를 통해 호출
	virtual void OffCollision();
	// 공격 실행
	virtual void OnAttack();
	// 공격 종료
	virtual void OnReset();
	
	UFUNCTION(Category = "Getter")
	bool GetIsEquip() const { return IsEquip; }
	
protected:
	// BeginPlay
	virtual void BeginPlay() override;
	// 루트
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
	// Weapon Data
	TArray<FWeaponData*> WeaponData;

	bool IsEquip; // 무기 장착 유무
};
