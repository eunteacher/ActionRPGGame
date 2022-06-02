#include "Charactets/CBaseCharacter.h"
#include "ActionRPGGame.h"
#include "Components/CFootStepSoundComponent.h"
#include "Components/CSoundComponent.h"
#include "Components/CMontageComponent.h"
#include "Components/CStateComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
// 생성자
ACBaseCharacter::ACBaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// 컴포넌트 생성
	Sound = CreateDefaultSubobject<UCSoundComponent>("Sound");
	FootStepSound = CreateDefaultSubobject<UCFootStepSoundComponent>("FootStepSound");
	Montage = CreateDefaultSubobject<UCMontageComponent>("Montage");
	State = CreateDefaultSubobject<UCStateComponent>("State");
	// 멤버변수 초기화
	Speed = ESpeedType::Walk;
	Weapon = EWeaponType::Default;
}

// BeginPlay
void ACBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	// State 컴포넌트의 델리게이트를 바인딩
	State->OnChangedState.AddDynamic(this, &ACBaseCharacter::OnChangedState);
}

// Tick
void ACBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// SetupPlayerInputComponent
void ACBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

// 캐릭터가 착지한 경우
// 그에 해당하는 행동들 정의
void ACBaseCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);
	// 착지 사운드
	if (IsValid(Sound))
	{
		Sound->PlayLandSound();
		State->SetState(EStateType::Idle_Walk_Run);
	}
}

void ACBaseCharacter::OnChangedState(EStateType InPrev, EStateType InNew)
{
}

void ACBaseCharacter::SetMaxSpeed(ESpeedType InSpeed)
{
	// InSpeed 값에 따라 MaxWalkSpeed 값과 SpeedType을 변경
	if (InSpeed == ESpeedType::Walk)
	{
		Speed = ESpeedType::Walk;
		GetCharacterMovement()->MaxWalkSpeed = 200.0f;
	}
	else if (InSpeed == ESpeedType::Run)
	{
		Speed = ESpeedType::Run;
		GetCharacterMovement()->MaxWalkSpeed = 600.0f;
	}
}
