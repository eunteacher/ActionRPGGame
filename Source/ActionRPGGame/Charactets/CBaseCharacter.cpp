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
	SpeedType = ESpeedType::Walk;
	WeaponType = EWeaponType::Default;
}

// BeginPlay
void ACBaseCharacter::BeginPlay()
{
	// State 컴포넌트의 델리게이트를 바인딩
	State->OnStateTypeChanged.AddDynamic(this, &ACBaseCharacter::OnStateTypeChanged);
	
	Super::BeginPlay();
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
		State->SetStateType(EStateType::Idle_Walk_Run);
	}
}
// State가 변경되었을 때 호출되는 함수
// 이전 StateType과 변경된 StateType을 입력으로 받는다.
void ACBaseCharacter::OnStateTypeChanged(EStateType InPrev, EStateType InNew)
{
	switch(InNew)
	{
	case EStateType::Idle_Walk_Run:
		if(InPrev == EStateType::UnEquip)
		{
			// 이전 State가 Unequip이었다면 WeaponType을 Default로 변경
			WeaponType = EWeaponType::Default;
		}
		else if(InPrev == EStateType::Attack)
		{
			// 공격이 종료되었기 때문에 모든 변수를 Reset
			if(EquipedWeaponDataMaps.Contains(WeaponType))
			{
				const FEquipedWeaponData equipedWeapon = EquipedWeaponDataMaps[WeaponType];
				// Weapon의 OnReset() 호출
				equipedWeapon.Weapon->OnReset();
			}
		}
		break;

	default:
		break;
	}
}

// 입력으로 SpeedType을 받고, 입력받은 SpeedType으로 변경하고 MaxWalkSpeed 값을 변경
void ACBaseCharacter::SetMaxSpeed(ESpeedType InSpeed)
{
	// InSpeed 값에 따라 MaxWalkSpeed 값과 SpeedType을 변경
	if (InSpeed == ESpeedType::Walk)
	{
		SpeedType = ESpeedType::Walk;
		GetCharacterMovement()->MaxWalkSpeed = 200.0f;
	}
	else if (InSpeed == ESpeedType::Run)
	{
		SpeedType = ESpeedType::Run;
		GetCharacterMovement()->MaxWalkSpeed = 600.0f;
	}
}
