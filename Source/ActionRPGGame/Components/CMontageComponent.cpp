#include "Components/CMontageComponent.h"
#include "ActionRPGGame.h"
#include "Charactets/CBaseCharacter.h"
#include "GameFramework/Character.h"
// 생성자 
UCMontageComponent::UCMontageComponent()
{
	// 데이터 테이블 에셋을 가져와 저장
	// DataTable'/Game/DataTables/DT_Montage.DT_Montage'
	static ConstructorHelpers::FObjectFinder<UDataTable> MontageTableAsset(TEXT("DataTable'/Game/DataTables/DT_Montage.DT_Montage'"));
	if (MontageTableAsset.Succeeded())
	{
		MontageTable = MontageTableAsset.Object;
	}
}

void UCMontageComponent::BeginPlay()
{
	Super::BeginPlay();

	// 데이터 테이블 값을 가져온다.
	if(IsValid(MontageTable))
	{
		// 데이터 테이블의 Data를 가져와 MontageData에 저장
		MontageTable->GetAllRows<FMontageData>("", MontageData);
	}
	else
	{
		CLog::Log("Montage Table Fail");
	}
	
}

void UCMontageComponent::PlayMontage(const EModelType InModelType, const EMontageType InMontageType)
{
	// MontageData InMontageType 해당하는 데이터를 찾는다.
	const FMontageData* data = MontageData[(int32)InMontageType];
	ACBaseCharacter* ownerCharacter = GetOwner<ACBaseCharacter>(); // Owner 가져오기
	// data가 존재하고, ownerCharacter가 존재하고, 캐릭터의 ModelType과 입력받은 ModelType이 같다면
	if (data != nullptr && IsValid(ownerCharacter) && ownerCharacter->GetModelType() == InModelType)
	{
		if (IsValid(data->AnimMontageMaps[InModelType]))
		{
			// 몽타주 실행
			ownerCharacter->PlayAnimMontage(data->AnimMontageMaps[InModelType], data->PlayRatio, data->StartSection);
		}

		if (IsValid(data->Particle))
		{
			// 파티클 스폰
			UGameplayStatics::SpawnEmitterAttached(data->Particle, ownerCharacter->GetMesh(), data->SocketName);
		}
	}
	else
	{
		CLog::Log("Montage Data Fail");
	}
}
