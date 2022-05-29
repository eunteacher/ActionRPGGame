#include "Components/CSoundComponent.h"
#include "ActionRPGGame.h"
#include "GameFramework/Character.h"

// 생성자
UCSoundComponent::UCSoundComponent()
{
	// 데이터 테이블 에셋을 가져와 저장
	// DataTable'/Game/DataTables/DT_Sound.DT_Sound'
	static ConstructorHelpers::FObjectFinder<UDataTable> SoundTableAsset(TEXT("DataTable'/Game/DataTables/DT_Sound.DT_Sound'"));
	if (SoundTableAsset.Succeeded())
	{
		SoundTable = SoundTableAsset.Object;
	}

	OwnerCharacter = Cast<ACharacter>(GetOwner()); // Owner Character 가져오기
}

// BeginPlay
void UCSoundComponent::BeginPlay()
{
	Super::BeginPlay();

	// 데이터 테이블 값을 가져온다.
	if (IsValid(SoundTable))
	{
		TArray<FSoundData*> soundDatas;
		SoundTable->GetAllRows<FSoundData>("", soundDatas);

		for (FSoundData* data : soundDatas)
		{
			if (ModelType == data->Type) // 모델 타입과 데이터의 타입이 같다면
			{
				SoundData = data;
			}
		}
	}
}

// Play Jump Sound
// OwnerCharacter의 위치에서 JumpSound를 Play
void UCSoundComponent::PlayJumpSound()
{
	if (SoundData->Jump != nullptr && IsValid(OwnerCharacter))
	{
		CLog::Log("Play Jump Sound");
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), SoundData->Jump, OwnerCharacter->GetActorLocation(), OwnerCharacter->GetActorRotation());
	}
}
// Play Land Sound
// OwnerCharacter의 위치에서 LandSound를 Play
void UCSoundComponent::PlayLandSound()
{
	if (SoundData->Land != nullptr && IsValid(OwnerCharacter))
	{
		CLog::Log("Play Land Sound");
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), SoundData->Land, OwnerCharacter->GetActorLocation(), OwnerCharacter->GetActorRotation());
	}
}
// Play Evade Sound
// OwnerCharacter의 위치에서 EvadeSound를 Play
void UCSoundComponent::PlayEvadeSound()
{
	if (SoundData->Evade != nullptr && IsValid(OwnerCharacter))
	{
		CLog::Log("Play Evade Sound");
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), SoundData->Evade, OwnerCharacter->GetActorLocation(), OwnerCharacter->GetActorRotation());
	}
}



