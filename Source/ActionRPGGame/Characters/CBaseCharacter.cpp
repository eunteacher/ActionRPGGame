#include "Characters/CBaseCharacter.h"
#include "ActionRPGGame.h"
#include "CGameInstance.h"
#include "CPlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CFootStepSoundComponent.h"
#include "Components/CSoundComponent.h"
#include "Components/CMontageComponent.h"
#include "Types/CDamageType.h"
#include "Weapon/CWeapon.h"

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
	AbilityType = EAbilityType::None;
}

// BeginPlay
void ACBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(GetGameInstance<UCGameInstance>()))
	{
		UDataTable* statusTable = GetGameInstance<UCGameInstance>()->ReadStatusTable();

		// 데이터 테이블의 값을 가져올 배열
		TArray<FStatusData*> statusDatas;
		statusTable->GetAllRows<FStatusData>("", statusDatas);

		for (FStatusData* statusData : statusDatas)
		{
			if (statusData->Type == StatusType)
			{
				UseStatusData = statusData;
				break;
			} // if type
		} // for statusData
	}
}

bool ACBaseCharacter::GetIsAiming()
{
	if (WeaponType == EWeaponType::Bow)
	{
		return EquipWeaponDataMaps.Find(WeaponType)->IsAiming;
	}
	
	return false;
}

FGenericTeamId ACBaseCharacter::GetGenericTeamId() const
{
	return TeamID;
}

void ACBaseCharacter::OnDead()
{
	// 무기 삭제
	for(auto& equipWeaponData : EquipWeaponDataMaps)
	{
		if (IsValid(equipWeaponData.Value.Weapon))
		{
			equipWeaponData.Value.Weapon->Destroy();
		}
	}
	
	// 캐릭터 삭제
	Destroy();
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
	float damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	UCDamageType* damageType = Cast<UCDamageType>(DamageEvent.DamageTypeClass->GetDefaultObject());

	return damage;
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
