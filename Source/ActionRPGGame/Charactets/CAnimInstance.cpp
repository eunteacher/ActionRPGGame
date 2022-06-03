#include "Charactets/CAnimInstance.h"
#include "ActionRPGGame.h"
#include "CBaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
// #include "Components/CStateComponent.h"

void UCAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
	OwnerCharacter = Cast<ACBaseCharacter>(TryGetPawnOwner());
}

void UCAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	
	if (IsValid(OwnerCharacter))
	{
		Speed = OwnerCharacter->GetVelocity().Size2D(); // 속도의 크기
		Velocity = OwnerCharacter->GetVelocity(); // 속력
		// OwnerCharacter의 속도와 OwnerCharacter의 방향으로 방향 계산
		Direction = UKismetAnimationLibrary::CalculateDirection(OwnerCharacter->GetVelocity(), OwnerCharacter->GetActorRotation());
		// 낙하 판단
		IsFall = OwnerCharacter->GetCharacterMovement()->IsFalling();
		// 현재 움직임 판단 
		IsMoving = Speed > 3.0f && !UKismetMathLibrary::EqualEqual_VectorVector(OwnerCharacter->GetCharacterMovement()->GetCurrentAcceleration(), FVector(0.0f, 0.0f, 0.0f),0.0f) ? true : false;
		// 앉기 판단
		IsCrouch = OwnerCharacter->bIsCrouched;
	}
}
