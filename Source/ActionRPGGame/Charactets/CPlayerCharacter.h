#pragma once

#include "CoreMinimal.h"
#include "Charactets/CBaseCharacter.h"
#include "Engine/DataTable.h"
#include "CPlayerCharacter.generated.h"

// 전방 선언
enum class EMontageType : uint8;
class ACWeapon_Base;
class ACWeapon_Sword;
// Player Character
UCLASS()
class ACTIONRPGGAME_API ACPlayerCharacter : public ACBaseCharacter
{
	GENERATED_BODY()

public:
	// 생성자
	ACPlayerCharacter();
	// Tick
	virtual void Tick(float DeltaTime) override;
	// SetupPlayerInputComponent
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// 체력 위젯 업데이트
	UFUNCTION()
	void UpdateHealth(float& InHealth, float& InMaxHealth);
	// 마나 위젯 업데이트
	UFUNCTION()
	void UpdateMana(float& InMana, float& InMaxMana);
	// 스테미나 위젯 업데이트
	UFUNCTION()
	void UpdateStamina(float& InStamina, float& InMaxStamina);

	// 현재 장착 중인 무기를 반환
	ACWeapon_Base* GetCurrentWeapon() const { return CurrentWeapon; }
protected:
	// BeginPlay
	virtual void BeginPlay() override;

	// Bind Axis
	UFUNCTION()
	void MoveForward(float InValue); // 앞 뒤 입력

	UFUNCTION()
	void MoveRight(float InValue); // 좌 우 입력

	UFUNCTION()
	void TurnAtRate(float InRate); // 마우스 X축

	UFUNCTION()
	void LookUpAtRate(float InRate); // 마우스 Y축

	// Bind Action
	UFUNCTION()
	void OnJump();

	UFUNCTION()
	void OffJump();

	UFUNCTION()
	void OnWalk();

	UFUNCTION()
	void OnRun();

	UFUNCTION()
	void OnCrouch();

	UFUNCTION()
	void OffCrouch();

	UFUNCTION()
	void OnEvade();

	UPROPERTY(VisibleDefaultsOnly, Category = "Camera")
	class USpringArmComponent* SpringArm; // SpringArm 컴포넌트

	UPROPERTY(VisibleDefaultsOnly, Category = "Camera")
	class UCameraComponent* Camera; // Camera 컴포넌트

	UPROPERTY(VisibleDefaultsOnly, Category = "Camera")
	float TurnRate; // 회전 비율

	UPROPERTY(VisibleDefaultsOnly, Category = "DataTable")
	UDataTable* StatusTable; // 데이터 테이블

	UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
	TSubclassOf<ACWeapon_Sword> NearWeaponClass;
	
	UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
	ACWeapon_Base* CurrentWeapon;

private:
	// Status 데이터
	struct FStatusData* StatusData;

	UPROPERTY()
	ACWeapon_Sword* NearWeapon; // 근접 무기
	// UPROPERTY()
	// ACWeapon_Base* FarWeapon; // 원거리 무기
};
