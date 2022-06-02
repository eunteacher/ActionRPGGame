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

	// State 변경 시 호출
	virtual void OnChangedState(EStateType InPrev, EStateType InNew) override;
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

	UFUNCTION()
	void OnEquip();

	UFUNCTION()
	void OnUnequip();

	UPROPERTY(VisibleDefaultsOnly, Category = "Camera")
	class USpringArmComponent* SpringArm; // SpringArm 컴포넌트

	UPROPERTY(VisibleDefaultsOnly, Category = "Camera")
	class UCameraComponent* Camera; // Camera 컴포넌트

	UPROPERTY(VisibleDefaultsOnly, Category = "Camera")
	float TurnRate; // 회전 비율

	UPROPERTY(VisibleDefaultsOnly, Category = "DataTable")
	UDataTable* StatusTable; // 데이터 테이블

private:
	// Status 데이터
	struct FStatusData* StatusData;
};
