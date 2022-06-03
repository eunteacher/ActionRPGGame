#include "Components/CStateComponent.h"

// 생성자
UCStateComponent::UCStateComponent()
{
	// PrimaryComponentTick.bCanEverTick = true;
}
// BeginPlay
void UCStateComponent::BeginPlay()
{
	Super::BeginPlay();
}

bool UCStateComponent::CheckStateTypeChanged(EStateType InNew, EStateType InPrev)
{
	// TODO : State 별 조건 체크
	return true;
}

// StatTpye을 변경, 델리게이트에 바인딩되어 있는 함수 호출
void UCStateComponent::SetStateType(EStateType InNew)
{
	const EStateType prev = StateType; // 이전 State Type
	if(CheckStateTypeChanged(InNew, prev)) // 변경 가능한지 확인
	{
		StateType = InNew;
		// 델리게이트 호출
		if(OnStateTypeChanged.IsBound())
		{
			OnStateTypeChanged.Broadcast(prev, StateType);
		}
	}
}

