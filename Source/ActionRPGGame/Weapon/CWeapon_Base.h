#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameFramework/Actor.h"
#include "CWeapon_Base.generated.h"

// 전방 선언
enum class EWeaponType : uint8;

UCLASS()
class ACTIONRPGGAME_API ACWeapon_Base : public AActor
{
	GENERATED_BODY()
	
public:	
	ACWeapon_Base();

	// 무기 장착 몽타주 실행 및 무기 장착 여부 설정
	void OnEquip();
	// 무기 해제 몽타주 실행 및 무기 장착 여부 설정
	void OnUnequip();
	// 무기를 입력받는 Socket에 붙인다.
	void OnAttach(FName InSocketName);

	// WeaponType을 반환
	EWeaponType GetCurrentWeaponType() const { return WeaponType; }
protected:
	// 루트
	UPROPERTY(VisibleDefaultsOnly, Category = "Component")
	USceneComponent* Root;
	// WeaponType
	UPROPERTY(VisibleDefaultsOnly, Category = "Type")
	EWeaponType WeaponType;
	// WeaponDataTable
	UPROPERTY(VisibleDefaultsOnly, Category = "DataTable")
	UDataTable* WeaponDataTable;

private:
	bool bEquip; // 무기 장착 유무
};
