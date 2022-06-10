#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CAnimInstance_Bow.generated.h"

// 전방 선언
class ACBaseCharacter;
class ACWeapon_Far;

UCLASS()
class ACTIONRPGGAME_API UCAnimInstance_Bow : public UAnimInstance
{
	GENERATED_BODY()

public:
	// Update 함수	
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	void InitAnimInstance(ACBaseCharacter* InOwnerCharacter);

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Variable")
	ACBaseCharacter* OwnerCharacter;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Variable")
	float BowCharge;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Variable")
	bool IsOverDraw;
};
