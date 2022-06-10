#include "Charactets/CBaseCharacter.h"
#include "ActionRPGGame.h"
#include "CPlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CFootStepSoundComponent.h"
#include "Components/CSoundComponent.h"
#include "Components/CMontageComponent.h"
#include "Weapon/CWeapon_Base.h"

// 생성자
ACBaseCharacter::ACBaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// 컴포넌트 생성
	Sound = CreateDefaultSubobject<UCSoundComponent>("Sound");
	FootStepSound = CreateDefaultSubobject<UCFootStepSoundComponent>("FootStepSound");
	Montage = CreateDefaultSubobject<UCMontageComponent>("Montage");

	// 멤버변수 초기화
	SpeedType = ESpeedType::Walk;
	WeaponType = EWeaponType::Default;
}

bool ACBaseCharacter::GetIsAiming()
{
	if (WeaponType == EWeaponType::Bow)
	{
		return EquipedWeaponDataMaps.Find(WeaponType)->IsAiming;
	}
	
	return false;
}

// BeginPlay
void ACBaseCharacter::BeginPlay()
{
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
	}
}

float ACBaseCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
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

// UnEquip 후 호출된다.
// WeaponType을 Default로 설정
void ACBaseCharacter::SetDefaultWeapon()
{
	WeaponType = EWeaponType::Default;
}
