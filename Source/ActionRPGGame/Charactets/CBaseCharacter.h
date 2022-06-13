#pragma once

#include "CoreMinimal.h"
#include "Types/CEnumTypes.h"
#include "Types/CStructTypes.h"
#include "Engine/DataTable.h"
#include "GameFramework/Character.h"
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

	// Take Damage
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	// 캐릭터의 최대 스피드 값을 설정
	UFUNCTION(Category = "Setter")
	void SetMaxSpeed(ESpeedType InSpeed);

	UFUNCTION(Category = "Setter")
	virtual void SetDefaultWeapon();
	
	// 현재 SpeedType을 반환
	UFUNCTION(Category = "Getter")
	ESpeedType GetSpeedType() const { return SpeedType; }

	// ModelType을 반환
	UFUNCTION(Category = "Getter")
	EModelType GetModelType() const { return ModelType; }

	// Weapon Type을 반환
	UFUNCTION(Category = "Getter")
	EWeaponType GetWeaponType() const { return WeaponType; }

	UFUNCTION(Category = "Getter")
	EStatusType GetStatusType() const { return StatusType; }

	// EquipedWeaponDataMaps을 반환
	UFUNCTION(Category = "Getter")
	TMap<EWeaponType, FEquipedWeaponData>& GetEquipedWeaponDataMaps() { return EquipedWeaponDataMaps; }

	UFUNCTION(Category = "Getter")
	bool GetIsAiming();
	
	void OnDead();
protected:
	// BeginPlay 함수
	virtual void BeginPlay() override;
	// Land 함수
	virtual void Landed(const FHitResult& Hit) override;

	// 왼발, 오른발 표면을 검사하여 표면에 맞는 사운드를 Play
	UPROPERTY(VisibleDefaultsOnly, Category = "Component")
	class UCFootStepSoundComponent* FootStepSound; // FootStep 컴포넌트

	// 캐릭터의 Sound Play를 담당
	UPROPERTY(VisibleDefaultsOnly, Category = "Component")
	class UCSoundComponent* Sound; // Sound 컴포넌트 

	// 몽타주 Play를 담당
	UPROPERTY(VisibleDefaultsOnly, Category = "Component")
	class UCMontageComponent* Montage; // Montage 컴포넌트

	// 캐릭터의 SpeedType
	UPROPERTY(VisibleDefaultsOnly, Category = "Type")
	ESpeedType SpeedType;

	// 캐릭터의 ModelType
	UPROPERTY(VisibleDefaultsOnly, Category = "Type")
	EModelType ModelType;

	// 캐릭터의 WeaponType
	UPROPERTY(VisibleDefaultsOnly, Category = "Type")
	EWeaponType WeaponType;

	UPROPERTY(VisibleDefaultsOnly, Category = "Type")
	EStatusType StatusType;

	// 캐릭터의 Status Data Table
	UPROPERTY(VisibleDefaultsOnly, Category = "DataTable")
	UDataTable* StatusTable;

	// Player 무기 데이터 테이블
	UPROPERTY(VisibleDefaultsOnly, Category = "DataTable")
	UDataTable* WeaponTable;

	// Status 데이터
	FUseStatusData UseStatusData;

	// 장착 무기 데이터 Map
	TMap<EWeaponType, FEquipedWeaponData> EquipedWeaponDataMaps;
};
