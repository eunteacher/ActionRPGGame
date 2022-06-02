#include "Components/CSoundComponent.h"
#include "ActionRPGGame.h"
#include "Charactets/CBaseCharacter.h"
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
}

// BeginPlay
void UCSoundComponent::BeginPlay()
{
	Super::BeginPlay();

	// 데이터 테이블 값을 가져온다.
	if (IsValid(SoundTable) && IsValid(GetOwner<ACBaseCharacter>()))
	{
		TArray<FSoundData*> soundDatas;
		SoundTable->GetAllRows<FSoundData>("", soundDatas);

		for (FSoundData* data : soundDatas)
		{
			// ModelType과 맞는 사운드 데이터를 가져와 저장
			if (GetOwner<ACBaseCharacter>()->GetModel() == data->Type) // 모델 타입과 데이터의 타입이 같다면
			{
				SoundData = data;
				break;
			}
		}
	}
}

// Play Jump Sound
// OwnerCharacter의 위치에서 JumpSound를 Play
void UCSoundComponent::PlayJumpSound()
{
	if (SoundData->Jump != nullptr && IsValid(GetOwner<ACBaseCharacter>()))
	{
		CLog::Log("Play Jump Sound");
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), SoundData->Jump, GetOwner<ACBaseCharacter>()->GetActorLocation(), GetOwner<ACBaseCharacter>()->GetActorRotation());
	}
}
// Play Land Sound
// OwnerCharacter의 위치에서 LandSound를 Play
void UCSoundComponent::PlayLandSound()
{
	if (SoundData->Land != nullptr && IsValid(GetOwner<ACBaseCharacter>()))
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), SoundData->Land, GetOwner<ACBaseCharacter>()->GetActorLocation(), GetOwner<ACBaseCharacter>()->GetActorRotation());
	}
}
// Play Evade Sound
// OwnerCharacter의 위치에서 EvadeSound를 Play
void UCSoundComponent::PlayEvadeSound()
{
	if (SoundData->Evade != nullptr && IsValid(GetOwner<ACBaseCharacter>()))
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), SoundData->Evade, GetOwner<ACBaseCharacter>()->GetActorLocation(), GetOwner<ACBaseCharacter>()->GetActorRotation());
	}
}

void UCSoundComponent::PlayEquipAndUnequipSound()
{
	if (SoundData->Evade != nullptr && IsValid(GetOwner<ACBaseCharacter>()))
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), SoundData->EquipAndUnequip, GetOwner<ACBaseCharacter>()->GetActorLocation(), GetOwner<ACBaseCharacter>()->GetActorRotation());
	}
}



