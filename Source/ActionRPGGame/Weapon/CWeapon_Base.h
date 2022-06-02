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
	// 생성자	
	ACWeapon_Base();

	// 무기 장착 몽타주 실행 및 무기 장착 여부 설정
	void OnEquip();
	// 무기 해제 몽타주 실행 및 무기 장착 여부 설정
	void OnUnequip();
	// 무기를 Onwer 캐릭터에 Attach, AnimNotify를 통해 호출
	void OnAttach(FName InSocketName);

	UFUNCTION(Category = "Getter")
	bool GetEquip() const { return bEquip; }
	
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
	UDataTable* WeaponDataTable;

private:
	bool bEquip; // 무기 장착 유무
};
