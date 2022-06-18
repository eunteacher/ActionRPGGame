#include "Components/CMontageComponent.h"
#include "ActionRPGGame.h"
#include "CGameInstance.h"
#include "Characters/CBaseCharacter.h"
#include "GameFramework/Character.h"

// 생성자 
UCMontageComponent::UCMontageComponent()
{

}

void UCMontageComponent::BeginPlay()
{
	Super::BeginPlay();

	// GameInstance에서 데이터 테이블 읽어오기
	if (IsValid(GetOwner<ACBaseCharacter>()->GetGameInstance<UCGameInstance>()))
	{
		UDataTable* montageTable = GetOwner<ACBaseCharacter>()->GetGameInstance<UCGameInstance>()->ReadMontageTable();

		if(IsValid(montageTable))
		{
			// DataTable에서 필요한 데이터를 UseMontageData에 담고, Map에 데이터 추가
			TArray<FMontageData*> montageDatas;
			montageTable->GetAllRows<FMontageData>("", montageDatas);
			for (FMontageData* montageData : montageDatas)
			{
				if (montageData->ModelType == GetOwner<ACBaseCharacter>()->GetModelType())
				{
					FUseMontageData useMontageData;
					useMontageData.AnimMontage = montageData->AnimMontage;
					useMontageData.PlayRatio = montageData->PlayRatio;
					useMontageData.StartSection = montageData->StartSection;
					UseMontageDataMaps.Add(montageData->MontageType, useMontageData);
				} // if type
			} // for MontageData		
		}
	}
}

// UseMontageMaps에서 Montage를 찾아 실행한다.
void UCMontageComponent::PlayMontage(const EMontageType InMontageType)
{
	// ownerCharacter가 존재할 경우
	if (IsValid(GetOwner<ACBaseCharacter>()))
	{
		if (UseMontageDataMaps.Contains(InMontageType))
		{
			// 몽타주 실행
			GetOwner<ACBaseCharacter>()->PlayAnimMontage(UseMontageDataMaps.Find(InMontageType)->AnimMontage, UseMontageDataMaps.Find(InMontageType)->PlayRatio, UseMontageDataMaps.Find(InMontageType)->StartSection);
		}
	}
	else
	{
		CLog::Log("Montage Data Fail");
	}
}
