#include "Charactets/CBaseCharacter.h"
#include "ActionRPGGame.h"
#include "CPlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CFootStepSoundComponent.h"
#include "Components/CSoundComponent.h"
#include "Components/CMontageComponent.h"
#include "Types/CDamageType.h"
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

	// Status 데이터 테이블 에셋을 가져와 저장
	// DataTable'/Game/DataTables/DT_Status.DT_Status'
	const ConstructorHelpers::FObjectFinder<UDataTable> statusTableAsset(TEXT("DataTable'/Game/DataTables/DT_Status.DT_Status'"));
	if (statusTableAsset.Succeeded())
	{
		StatusTable = statusTableAsset.Object;
	}
}

// BeginPlay
void ACBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	// 데이터 테이블의 값을 가져올 배열
	TArray<FStatusData*> statusDatas;
	StatusTable->GetAllRows<FStatusData>("", statusDatas);
	
	// Status 데이터 테이블 값을 저장
	for (FStatusData* data : statusDatas)
	{
		if (data->Type == StatusType)
		{
			UseStatusData = data;
			break;
		}
	}

}

bool ACBaseCharacter::GetIsAiming()
{
	if (WeaponType == EWeaponType::Bow)
	{
		return EquipedWeaponDataMaps.Find(WeaponType)->IsAiming;
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
	for(auto& equipedWeaponData : EquipedWeaponDataMaps)
	{
		if (IsValid(equipedWeaponData.Value.Weapon))
		{
			equipedWeaponData.Value.Weapon->Destroy();
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
