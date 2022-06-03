#pragma once

#include "CoreMinimal.h"
#include "Charactets/CBaseCharacter.h"
#include "Engine/DataTable.h"
#include "CPlayerCharacter.generated.h"

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
	void OnJump(); // 점프

	UFUNCTION()
	void OffJump(); // StopJump

	UFUNCTION()
	void OnWalk(); // 걷기

	UFUNCTION()
	void OnRun(); // 뛰기

	UFUNCTION()
	void OnCrouch(); // 앉기

	UFUNCTION()
	void OffCrouch(); // 일어서기

	UFUNCTION()
	void OnEvade(); // 피하기

	UFUNCTION()
	void OnEquip(); // 무기 장착

	UFUNCTION()
	void OnUnEquip(); // 무기 해제

	UFUNCTION()
	void OnAttack(); // 공격

	UPROPERTY(VisibleDefaultsOnly, Category = "Camera")
	class USpringArmComponent* SpringArm; // SpringArm 컴포넌트

	UPROPERTY(VisibleDefaultsOnly, Category = "Camera")
	class UCameraComponent* Camera; // Camera 컴포넌트

	UPROPERTY(VisibleDefaultsOnly, Category = "Camera")
	float TurnRate; // 회전 비율

	UPROPERTY(VisibleDefaultsOnly, Category = "DataTable")
	UDataTable* StatusTable; // 데이터 테이블

	// Status 데이터
	FStatusData* StatusData;
};
