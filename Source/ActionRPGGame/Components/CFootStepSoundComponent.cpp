#include "Components/CFootStepSoundComponent.h"
#include "ActionRPGGame.h"
#include "CGameInstance.h"
#include "Characters/CBaseCharacter.h"
#include "PhysicalMaterials/PhysicalMaterial.h"

// 생성자
UCFootStepSoundComponent::UCFootStepSoundComponent()
{
	LeftFoot = "FootStep_Left"; // 왼쪽 발
	RightFoot = "FootStep_Right"; // 오른쪽 발
	TraceType = ETraceTypeQuery::TraceTypeQuery2;
	DrawDebugType = EDrawDebugTrace::ForDuration;
}

// BeginPlay
void UCFootStepSoundComponent::BeginPlay()
{
	Super::BeginPlay();

	// GameInstance에서 데이터 테이블 읽어오기
	if (IsValid(GetOwner<ACBaseCharacter>()->GetGameInstance<UCGameInstance>()))
	{
		UDataTable* footStepSoundTable = GetOwner<ACBaseCharacter>()->GetGameInstance<UCGameInstance>()->ReadFootStepSoundTable();

		if(IsValid(footStepSoundTable))
		{
			// DataTable에서 값을 가져와 FootStepSoundData에 저장
			footStepSoundTable->GetAllRows<FFootStepSoundData>("", FootStepSoundData);
		}
	}
}
// 왼발 발자국 
void UCFootStepSoundComponent::NotifyLeftFootStep(const ESpeedType InType)
{
	const bool isRight = false;
	PlayFootStepSound(InType, isRight);
}
// 오른발 발자국
void UCFootStepSoundComponent::NotifyRightFootStep(const ESpeedType InType)
{
	const bool isRight = true;
	PlayFootStepSound(InType, isRight);
}

// 입력으로 SpeedType과 좌/우 판단 여부를 받는다.
// 트레이스를 통해 PhysicalSurface를 검사한 후 그에 맞는 사운드를 Play
void UCFootStepSoundComponent::PlayFootStepSound(const ESpeedType InType, const  bool IsRight)
{
	//CLog::Log("PlayFootStepSound");
	ACBaseCharacter* ownerCharacter = GetOwner<ACBaseCharacter>();
	if (IsValid(ownerCharacter))
	{
		// 위치 값 저장
		FVector socketLocation = FVector::ZeroVector; // 소켓 위치
		if (IsRight)
		{
			socketLocation = ownerCharacter->GetMesh()->GetSocketLocation(RightFoot);
		}
		else
		{
			socketLocation = ownerCharacter->GetMesh()->GetSocketLocation(LeftFoot);
		}

		// Line Trace 매개 변수 선언
		FVector start = FVector(socketLocation.X, socketLocation.Y, socketLocation.Z + 50);; // Trace 시작
		FVector end = FVector(socketLocation.X, socketLocation.Y, socketLocation.Z - 50); // Trace 끝
		FHitResult hit; // Hit 구조체
		TArray<AActor*> actorToIgnore; // Ignore Actor
		actorToIgnore.Add(ownerCharacter); // 소유하고 있는 캐릭터 추가

		// 트레이스 시작
		if (UKismetSystemLibrary::LineTraceSingle(GetWorld(), start, end, TraceType, false, actorToIgnore, DrawDebugType, hit, true))
		{
			// CLog::Log("Trace HitResult True");
			TEnumAsByte<EPhysicalSurface> physicalSurfaceType = UPhysicalMaterial::DetermineSurfaceType(hit.PhysMaterial.Get());
			if(FootStepSoundData[(int32)physicalSurfaceType] == nullptr)
			{
				CLog::Log("FootStepData nullptr");
				return;
			}

			// Play Sound
			// 현재 위치에서 Sound Play
			if (InType == ESpeedType::Walk)
			{
				UGameplayStatics::PlaySoundAtLocation(GetWorld(), FootStepSoundData[(int32)physicalSurfaceType]->WalkSound, ownerCharacter->GetActorLocation(), ownerCharacter->GetActorRotation());
			}
			else if (InType == ESpeedType::Run)
			{
				UGameplayStatics::PlaySoundAtLocation(GetWorld(), FootStepSoundData[(int32)physicalSurfaceType]->RunSound, ownerCharacter->GetActorLocation(), ownerCharacter->GetActorRotation());
			}

			// TODO : Effect Spawn
		}
	}
	else
	{
		CLog::Log("UCFootStepSoundComponent::PlayFootStepSound() : Owner Fail");
	}
}
