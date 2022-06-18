#include "Weapon/CWeapon_Far.h"
#include "ActionRPGGame.h"
#include "Camera/CameraComponent.h"
#include "Characters/CBaseCharacter.h"
#include "Components/CMontageComponent.h"
#include "GameFramework/SpringArmComponent.h"

ACWeapon_Far::ACWeapon_Far()
{
	PrimaryActorTick.bCanEverTick = true;

	IsAiming = false;
	IsOverDraw = false;
}

void ACWeapon_Far::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(IsAiming)
	{
		TargetTrace();
	}
}

void ACWeapon_Far::BeginPlay()
{
	Super::BeginPlay();

	// Owner Character의 Camera과 SpringArm 컴포넌트 가져오기
	OwnerSpringArm = Cast<USpringArmComponent>(GetOwner<ACBaseCharacter>()->GetComponentByClass(USpringArmComponent::StaticClass()));
	OwnerCamera = Cast<UCameraComponent>(GetOwner<ACBaseCharacter>()->GetComponentByClass(UCameraComponent::StaticClass()));

}

// Bow_Attack 실행 함수
// 몽타주만 실행하고, 화살 생성은 OnFire()에서 진행한다.
void ACWeapon_Far::OnAttack()
{
	Super::OnAttack();

	CLog::Log("Far On Attack");
	if(IsAiming && !IsAttack)
	{
		IsAttack = true;
		IsOverDraw = false;
		AttackType = EAttackType::Far_Fire;

		// OwnerCharacter의 montage 컴포넌트를 가져온다.
		UCMontageComponent* montage = Cast<UCMontageComponent>(GetOwner<ACBaseCharacter>()->GetComponentByClass(UCMontageComponent::StaticClass()));
		if(IsValid(montage))
		{
			montage->PlayMontage(UseWeaponDataMaps.Find(AttackType)->MontageType);
		}
	}
}

void ACWeapon_Far::OnReset()
{
	Super::OnReset();

	// 에임 상태라면
	if(IsAiming)
	{
		// OwnerCharacter의 Montage 컴포넌트를 가져와 AttackType에 맞는 몽타주를 실행한다.
		UCMontageComponent* montage = Cast<UCMontageComponent>(GetOwner<ACBaseCharacter>()->GetComponentByClass(UCMontageComponent::StaticClass()));
		if (IsValid(montage))
		{
			AttackType = EAttackType::Far_OverDraw;
			if(UseWeaponDataMaps.Contains(AttackType))
			{
				montage->PlayMontage(UseWeaponDataMaps.Find(AttackType)->MontageType);
			}
		}
	}

	IsAttack = false;
}

void ACWeapon_Far::OnAim()
{
	Super::OnAim();

	CLog::Log("Far On Aim");
	if (IsValid(GetOwner<ACBaseCharacter>()) && IsValid(OwnerSpringArm) && IsValid(OwnerCamera))
	{
		// OwnerCharacter에서 IsAiming 값을 가져온다.
		IsAiming = GetOwner<ACBaseCharacter>()->GetIsAiming();

		// AttackType을 OverDraw 저장
		AttackType = EAttackType::Far_OverDraw;

		// OwnerCharacter에서 Montage 컴포넌트를 가져와 OverDraw 몽타주를 실행한다.
		UCMontageComponent* montage = Cast<UCMontageComponent>(GetOwner<ACBaseCharacter>()->GetComponentByClass(UCMontageComponent::StaticClass()));
		if (IsValid(montage) && UseWeaponDataMaps.Contains(AttackType))
		{
			montage->PlayMontage(UseWeaponDataMaps.Find(AttackType)->MontageType);
		}

		// TODO : 커브로 변경하기

		OwnerSpringArm->TargetArmLength = 250.0f;
		OwnerSpringArm->SocketOffset = FVector(0.0f, 45.0f, -30.0f);

		OwnerCamera->SetFieldOfView(60.0f);
	}
}

void ACWeapon_Far::OffAim()
{
	Super::OffAim();
	
	CLog::Log("Far Off Aim");
	// IsAiming이 true인 경우
	if (IsValid(GetOwner<ACBaseCharacter>()) && IsValid(OwnerSpringArm) && IsValid(OwnerCamera))
	{
		IsOverDraw = false;
		// OwnerCharacter에서 IsAiming 값을 가져온다.
		IsAiming = GetOwner<ACBaseCharacter>()->GetIsAiming();

		// SpringArm 
		OwnerSpringArm->TargetArmLength = 600.0f;
		OwnerSpringArm->SocketOffset = FVector(0.0f,0.0f,0.0f);
		// Camera
		OwnerCamera->SetFieldOfView(90.0f);
	}
}

bool ACWeapon_Far::GetIsOverDraw()
{
	return IsOverDraw;
}

void ACWeapon_Far::SetIsOverDraw(bool InIsOverDraw)
{
	IsOverDraw = InIsOverDraw;
}

bool ACWeapon_Far::TargetTrace()
{
	// Debug Type
	TEnumAsByte<EDrawDebugTrace::Type> drawDebugType = EDrawDebugTrace::None;
	// 트레이스 타입 
	TEnumAsByte<ETraceTypeQuery> traceType = ETraceTypeQuery::TraceTypeQuery2;

	// Line Trace 매개 변수 선언
	// Trace 시작 위치
	FVector start = OwnerCamera->GetComponentLocation();
	// Trace 끝 위치
	FVector end = start + (OwnerCamera->GetForwardVector() * 1000000.0f);
	FHitResult hit; // Hit 구조체
	TArray<AActor*> actorToIgnore; // Ignore Actor
	actorToIgnore.Add(GetOwner<ACBaseCharacter>()); // 소유하고 있는 캐릭터 추가

	if (UKismetSystemLibrary::LineTraceSingle(GetWorld(), start, end, traceType, false, actorToIgnore, drawDebugType, hit, true))
	{
		// CLog::Log("Find Target");
		return true;
	}

	// CLog::Log("Fail Find Target");
	return false;
}


