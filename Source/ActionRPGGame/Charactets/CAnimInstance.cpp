#include "Charactets/CAnimInstance.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
// #include "Components/CStateComponent.h"

void UCAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
	OwnerCharacter = Cast<ACharacter>(TryGetPawnOwner());
}

void UCAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (OwnerCharacter != nullptr)
	{
		Speed = OwnerCharacter->GetVelocity().Size2D(); // 속도의 크기
		Velocity = OwnerCharacter->GetVelocity(); // 속력
		// OwnerCharacter의 속도와 OwnerCharacter의 방향으로 방향 계산
		Direction = UKismetAnimationLibrary::CalculateDirection(OwnerCharacter->GetVelocity(), OwnerCharacter->GetActorRotation());
		IsFall = OwnerCharacter->GetCharacterMovement()->IsFalling();
		IsMoving = Speed > 3.0f && !UKismetMathLibrary::EqualEqual_VectorVector(OwnerCharacter->GetCharacterMovement()->GetCurrentAcceleration(), FVector(0.0f, 0.0f, 0.0f),0.0f) ? true : false;

		// UCStateComponent* state = Cast<UCStateComponent>(OwnerCharacter->GetComponentByClass(UCStateComponent::StaticClass()));
		//if(state != nullptr)
		//{
		//	 IsCrouch = EStateType::Crouch == state->GetCurrentStateType() ? true : false;
		//}
	}
}
