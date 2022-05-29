#include "Components/CMontageComponent.h"
#include "ActionRPGGame.h"
#include "GameFramework/Character.h"
// 생성자 
UCMontageComponent::UCMontageComponent()
{
	// 데이터 테이블 에셋을 가져와 저장
	// DataTable'/Game/DataTables/DT_GL_Montage.DT_GL_Montage'
	static ConstructorHelpers::FObjectFinder<UDataTable> MontageTableAsset(TEXT("DataTable'/Game/DataTables/DT_GL_Montage.DT_GL_Montage'"));
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
		TArray<FMontageData*> montageDatas;
		MontageTable->GetAllRows<FMontageData>("", montageDatas);
		for (int32 i = 0; i < (int32)EMontageType::Max; i++)
		{
			for (FMontageData* data : montageDatas)
			{
				if ((EMontageType)i == data->Type)
				{
					MontageData[i] = data;
				}
			}
		}
	}
	else
	{
		CLog::Log("Montage Table Fail");
	}
	
}

void UCMontageComponent::PlayMontage(const EMontageType InType)
{
	// InType에 해당하는 데이터를 가져온다.
	const FMontageData* data = MontageData[(int32)InType];
	ACharacter* ownerCharacter = Cast<ACharacter>(GetOwner()); // Owner 가져오기
	if(data != nullptr && IsValid(ownerCharacter))
	{
		if (data->AnimMontage != nullptr)
		{
			// 몽타주 실행
			ownerCharacter->PlayAnimMontage(data->AnimMontage, data->PlayRatio, data->StartSection);
		}

		if (data->Particle != nullptr)
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
