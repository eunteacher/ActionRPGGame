#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CAnimInstance.generated.h"

UCLASS()
class ACTIONRPGGAME_API UCAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeBeginPlay() override;
	// Update 함수	
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	FRotator LookUpRotation();

	UPROPERTY(BlueprintReadOnly,EditAnywhere,Category="Character")
	class ACBaseCharacter* OwnerCharacter;
	// 속력
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Variable")
	float Speed;
	// 속도
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Variable")
	FVector Velocity;
	// 방향
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Variable")
	float Direction;
	// 낙하 상태 
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Variable")
	bool IsFall;
	// 캐릭터의 움직임 여부
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Variable")
	bool IsMoving;
	// 캐릭터의 앉기 여부
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Variable")
	bool IsCrouch;
	// Aim 판단
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Variable")
	bool IsAiming;
	// OwnerCharacter의 ComtrolRotation의 Pitch 값
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Variable")
	FRotator AimRotation;
};
