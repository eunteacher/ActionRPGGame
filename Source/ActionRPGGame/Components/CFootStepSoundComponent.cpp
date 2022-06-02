#include "Components/CFootStepSoundComponent.h"
#include "ActionRPGGame.h"
#include "Charactets/CBaseCharacter.h"
#include "GameFramework/Character.h"
#include "PhysicalMaterials/PhysicalMaterial.h"

// 생성자
UCFootStepSoundComponent::UCFootStepSoundComponent()
{
	// 데이터 테이블 에셋을 가져와 저장
	// DataTable'/Game/DataTables/DT_FootStepSound.DT_FootStepSound'
	static ConstructorHelpers::FObjectFinder<UDataTable> FootStepSoundTableAsset(TEXT("DataTable'/Game/DataTables/DT_FootStepSound.DT_FootStepSound'"));
	if (FootStepSoundTableAsset.Succeeded())
	{
		FootStepSoundTable = FootStepSoundTableAsset.Object;
	}

	// 멤버 변수 초기화
	LeftFoot = "FootStep_Left";
	RightFoot = "FootStep_Right";
	TraceType = ETraceTypeQuery::TraceTypeQuery2;
	DrawDebugType = EDrawDebugTrace::ForDuration;
}

// BeginPlay
void UCFootStepSoundComponent::BeginPlay()
{
	Super::BeginPlay();

	// 데이터 테이블 값을 가져온다.
	if (IsValid(FootStepSoundTable))
	{
		FootStepSoundTable->GetAllRows<FFootStepSoundData>("", FootStepSoundData);
	}
}
// 왼발 발자국 
void UCFootStepSoundComponent::NotifyLeftFootStep(const ESpeedType InSpeed)
{
	const bool isRight = false;
	PlayFootStepSound(InSpeed, isRight);
}
// 오른발 발자국
void UCFootStepSoundComponent::NotifyRightFootStep(const ESpeedType InSpeed)
{
	const bool isRight = true;
	PlayFootStepSound(InSpeed, isRight);
}

// 입력으로 SpeedType과 좌/우 판단 여부를 받는다.
// 트레이스를 통해 PhysicalSurface를 검사한 후 그에 맞는 사운드를 Play
void UCFootStepSoundComponent::PlayFootStepSound(const ESpeedType InSpeed, const  bool IsRight)
{
	//CLog::Log("PlayFootStepSound");
	ACBaseCharacter* ownerCharacter = GetOwner<ACBaseCharacter>();
	if (IsValid(ownerCharacter))
	{
		// Line Trace 매개 변수 선언
		FVector socketLocation; // 소켓 위치
		FVector start; // Trace 시작
		FVector end; // Trace 끝
		FHitResult hit; // Hit 구조체
		TArray<AActor*> actorToIgnore; // Ignore Actor
		actorToIgnore.Add(ownerCharacter); // 소유하고 있는 캐릭터 추가

		// 위치 값 저장
		if (IsRight)
		{
			socketLocation = ownerCharacter->GetMesh()->GetSocketLocation(RightFoot);
		}
		else
		{
			socketLocation = ownerCharacter->GetMesh()->GetSocketLocation(LeftFoot);
		}

		start = FVector(socketLocation.X, socketLocation.Y, socketLocation.Z + 50);
		end = FVector(socketLocation.X, socketLocation.Y, socketLocation.Z - 50);

		// 트레이스 시작
		if (UKismetSystemLibrary::LineTraceSingle(GetWorld(), start, end, TraceType, false, actorToIgnore, DrawDebugType, hit, true))
		{
			// CLog::Log("Trace HitResult True");
			TEnumAsByte<EPhysicalSurface> physicalSurfaceType = UPhysicalMaterial::DetermineSurfaceType(hit.PhysMaterial.Get());
			// 데이터가 없으면 종료
			if (FootStepSoundData[(int32)physicalSurfaceType] == nullptr)
			{
				CLog::Log("FootStepSoundData Fail ");
				return;
			}

			// Play Sound
			// 현재 위치에서 Sound Play
			if (InSpeed == ESpeedType::Walk)
			{
				UGameplayStatics::PlaySoundAtLocation(GetWorld(), FootStepSoundData[(int32)physicalSurfaceType]->WalkSound, ownerCharacter->GetActorLocation(), ownerCharacter->GetActorRotation());
			}
			else if (InSpeed == ESpeedType::Run)
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
