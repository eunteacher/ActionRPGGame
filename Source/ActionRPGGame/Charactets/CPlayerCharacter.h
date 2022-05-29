#pragma once

#include "CoreMinimal.h"
#include "Charactets/CBaseCharacter.h"
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
	
protected:
	// BeginPlay
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	class USpringArmComponent* SpringArm; // SpringArm 컴포넌트

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	class UCameraComponent* Camera; // Camera 컴포넌트

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Camera")
	float TurnRate; // 회전 비율

	// Bind Axis
	UFUNCTION()
	void MoveForward(float InValue);

	UFUNCTION()
	void MoveRight(float InValue);

	UFUNCTION()
	void TurnAtRate(float InRate);

	UFUNCTION()
	void LookUpAtRate(float InRate);

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

	virtual void OnHealthChanged(const FGameplayTagContainer& EventTags) override;
	virtual void OnManaChanged(const FGameplayTagContainer& EventTags) override;
	virtual void OnStaminaChanged(const struct FGameplayTagContainer& EventTags) override;
	virtual void OnWalkSpeedChanged(const struct FGameplayTagContainer& EventTags) override;
	virtual void OnRunSpeedChanged(const struct FGameplayTagContainer& EventTags) override;
};
