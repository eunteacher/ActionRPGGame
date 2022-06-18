#include "Characters/CAnimInstance.h"
#include "ActionRPGGame.h"
#include "CBaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

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
		// 속도의 크기
		Speed = OwnerCharacter->GetVelocity().Size2D();
		// 속력
		Velocity = OwnerCharacter->GetVelocity(); 
		// OwnerCharacter의 속도와 OwnerCharacter의 방향으로 방향 계산
		Direction = UKismetAnimationLibrary::CalculateDirection(OwnerCharacter->GetVelocity(), OwnerCharacter->GetActorRotation());
		// 낙하 판단
		IsFall = OwnerCharacter->GetCharacterMovement()->IsFalling();
		// 현재 움직임 판단 
		IsMoving = Speed > 3.0f && !UKismetMathLibrary::EqualEqual_VectorVector(OwnerCharacter->GetCharacterMovement()->GetCurrentAcceleration(), FVector(0.0f, 0.0f, 0.0f),0.0f) ? true : false;
		// 앉기 판단
		IsCrouch = OwnerCharacter->bIsCrouched;
		// 에임 여부 판단
		IsAiming = OwnerCharacter->GetIsAiming();
		// AimRotation 값 셋팅
		AimRotation = LookUpRotation();
	}
}
// Aim 상태에서 LookUp 회전 값을 가져오는 함수
FRotator UCAnimInstance::LookUpRotation()
{
	// 컨트롤러의 회전 값을 가져온다.
	FRotator r = OwnerCharacter->GetControlRotation();
	if(r.Pitch > 270.0f)
	{
		// 아래를 바라보는 경우 
		r.Pitch = 360.0f - r.Pitch;
	}
	else
	{
		// 위를 바라보는 경우
		r.Pitch *= -1.0f;
	}
	
	return FRotator(0.0f,0.0f,r.Pitch);
}
