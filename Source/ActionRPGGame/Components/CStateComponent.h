#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Types/CEnumTypes.h"
#include "CStateComponent.generated.h"

// 델리게이트
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnStateTypeChanged, EStateType, InPrevType, EStateType, InNewType);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONRPGGAME_API UCStateComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// 생성자
	UCStateComponent();

	// 현재 StateType을 반환
	UFUNCTION(Category = "Getter")
	EStateType GetStateType() const { return StateType; }

	// StateType을 변경
	UFUNCTION(Category = "Setter")
	void SetStateType(EStateType InNew);

	// 델리게이트, State가 변경될 경우 호출
	UPROPERTY()
	FOnStateTypeChanged OnStateTypeChanged;
protected:
	// BeginPlay
	virtual void BeginPlay() override;

	// 새로운 StateTpye과 이전 StateType을 비교하여 변경 가능 여부를 판단
	bool CheckStateTypeChanged(EStateType InNew, EStateType InPrev);

	// State Type
	UPROPERTY(VisibleDefaultsOnly, Category = "Type")
	EStateType StateType;
};
