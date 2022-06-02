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
		// 데이터 테이블의 Data를 가져와 montageDatas에 저장
		TArray<FMontageData*> montageDatas;
		MontageTable->GetAllRows<FMontageData>("", montageDatas);

		// ModelType에 맞게 몽타주를 저장
		for (int32 i = 0; i < (int32)EModelType::Max; i++)
		{
			TArray<FMontageData*> temp; // 임시 TArray
			for (FMontageData* data : montageDatas)
			{
				if(data->ModelType == (EModelType)i)
				{
					temp.Add(data);
				}
			}
			MontageDataMaps.Add((EModelType)i, temp);
		}
	}
	else
	{
		CLog::Log("Montage Table Fail");
	}
	
}

void UCMontageComponent::PlayMontage(const EModelType InModel, const EMontageType InMontage)
{
	// MontageDataMaps에서 InModel에 해당하는 TArray를 찾는다.
	TArray<FMontageData*> montageDatas = MontageDataMaps[InModel];
	// 찾은 TArray에서 InMontage에 해당하는 Data를 가져온다.
	const FMontageData* data = montageDatas[(int32)InMontage];
	ACBaseCharacter* ownerCharacter = GetOwner<ACBaseCharacter>(); // Owner 가져오기
	if (data != nullptr && IsValid(ownerCharacter) && ownerCharacter->GetModel() == InModel)
	{
		if (IsValid(data->AnimMontage))
		{
			// 몽타주 실행
			ownerCharacter->PlayAnimMontage(data->AnimMontage, data->PlayRatio, data->StartSection);
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
