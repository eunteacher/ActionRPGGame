#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameFramework/Character.h"
#include "Types/CDataTableType.h"
#include "Types/CEnumTypes.h"
#include "Types/CTypes.h"
#include "CBaseCharacter.generated.h"

// 기본 캐릭터 클래스
// Player와 Monster 모두 이 클래스를 상속 받는다.
UCLASS()
class ACTIONRPGGAME_API ACBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// 생성자
	ACBaseCharacter();
	// Tick 함수
	virtual void Tick(float DeltaTime) override;
	// SetupPlayerInputComponent 
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// 캐릭터의 최대 스피드 값을 설정
	UFUNCTION(Category = "Setter")
	void SetMaxSpeed(ESpeedType InSpeed);

	// 현재 SpeedType을 반환
	UFUNCTION(Category = "Getter")
	ESpeedType GetSpeed() const { return Speed; }

	// ModelType을 반환
	UFUNCTION(Category = "Getter")
	EModelType GetModel() const { return Model; }

	UFUNCTION(Category = "Getter")
	EWeaponType GetWeapon() const { return Weapon; }

	UFUNCTION(Category = "Getter")
	TMap<EWeaponType, FOwningWeapon> GetOwningWeaponDataMaps() { return OwningWeaponDataMaps; }
	
protected:
	// BeginPlay 함수
	virtual void BeginPlay() override;
	// Land 함수
	virtual void Landed(const FHitResult& Hit) override;
	// State 컴포넌트의 델리게이트에 바인딩된 함수
	virtual void OnChangedState(EStateType InPrev, EStateType InNew);
	
	// 왼발, 오른발 표면을 검사하여 표면에 맞는 사운드를 Play
	UPROPERTY(VisibleDefaultsOnly, Category = "Component")
	class UCFootStepSoundComponent* FootStepSound; // FootStep 컴포넌트

	// 캐릭터의 Sound Play를 담당
	UPROPERTY(VisibleDefaultsOnly, Category = "Component")
	class UCSoundComponent* Sound; // Sound 컴포넌트 

	// 몽타주 Play를 담당
	UPROPERTY(VisibleDefaultsOnly, Category = "Component")
	class UCMontageComponent* Montage; // Montage 컴포넌트

	// StateType을 변경 및 조건을 확인
	UPROPERTY(VisibleDefaultsOnly, Category = "Component")
	class UCStateComponent* State; // State 컴포넌트

	// 캐릭터의 SpeedType
	UPROPERTY(VisibleDefaultsOnly, Category = "Type")
	ESpeedType Speed;
	// 캐릭터의 ModelType
	UPROPERTY(VisibleDefaultsOnly, Category = "Type")
	EModelType Model;
	// 캐릭터의 WeaponType
	UPROPERTY(VisibleDefaultsOnly, Category = "Type")
	EWeaponType Weapon;

	UPROPERTY(VisibleDefaultsOnly, Category = "DataTable")
	UDataTable* OwningWeaponDataTable; // 소유 중인 무기 데이터 테이블

	TMap<EWeaponType, FOwningWeapon> OwningWeaponDataMaps; // 소유 중인 무기 데이터 Map
};
