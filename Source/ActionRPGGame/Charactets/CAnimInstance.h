#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CAnimInstance.generated.h"

UCLASS()
class ACTIONRPGGAME_API UCAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	// BeginPlay 함수
	virtual void NativeBeginPlay() override;
	// Update 함수	
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Variable")
	ACharacter* OwnerCharacter;
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
};
