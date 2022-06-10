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
		TArray<FMontageData* > montageDatas;
		MontageTable->GetAllRows<FMontageData>("", montageDatas);
		for(FMontageData* data : montageDatas)
		{
			if (data->ModelType == GetOwner<ACBaseCharacter>()->GetModelType())
			{
				FUseMontageData useMontageData;
				useMontageData.AnimMontage = data->AnimMontage;
				useMontageData.PlayRatio = data->PlayRatio;
				useMontageData.StartSection = data->StartSection;
				UseMontageDataMaps.Add(data->MontageType, useMontageData);
			}
		}
	}
	else
	{
		CLog::Log("Montage Table Fail");
	}
	
}

void UCMontageComponent::PlayMontage(const EMontageType InMontageType)
{
	ACBaseCharacter* ownerCharacter = GetOwner<ACBaseCharacter>(); // Owner 가져오기
	// ownerCharacter가 존재할 경우
	if (IsValid(ownerCharacter))
	{
		if (UseMontageDataMaps.Contains(InMontageType))
		{
			// 몽타주 실행
			ownerCharacter->PlayAnimMontage(UseMontageDataMaps.Find(InMontageType)->AnimMontage, UseMontageDataMaps.Find(InMontageType)->PlayRatio, UseMontageDataMaps.Find(InMontageType)->StartSection);
		}
	}
	else
	{
		CLog::Log("Montage Data Fail");
	}
}
