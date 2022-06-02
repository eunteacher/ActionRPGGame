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

bool UCStateComponent::CheckChangedState(EStateType InNew, EStateType InPrev)
{
	// TODO : State 별 조건 체크
	return true;
}

// StatTpye을 변경, 델리게이트에 바인딩되어 있는 함수 호출
void UCStateComponent::SetState(EStateType InNew)
{
	const EStateType prevState = State; // 이전 State Type
	if(CheckChangedState(InNew, prevState)) // 변경 가능한지 확인
	{
		State = InNew;
		// 델리게이트 호출
		if(OnChangedState.IsBound())
		{
			OnChangedState.Broadcast(prevState, State);
		}
	}
}

