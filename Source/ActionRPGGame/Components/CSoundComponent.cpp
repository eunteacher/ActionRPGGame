#include "Components/CSoundComponent.h"
#include "ActionRPGGame.h"
#include "Charactets/CBaseCharacter.h"

// 생성자
UCSoundComponent::UCSoundComponent()
{
	// Sound 데이터 테이블 에셋을 가져와 저장
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
	if (IsValid(SoundTable))
	{
		TArray<FSoundData*> soundDatas;
		SoundTable->GetAllRows<FSoundData>("", soundDatas);

		for (FSoundData* data : soundDatas)
		{
			// ModelType과 맞는 사운드 데이터를 가져와 저장
			if (data->Type == GetOwner<ACBaseCharacter>()->GetModelType()) // 모델 타입과 데이터의 타입이 같다면
			{
				SoundData = data;
				break;
			} // if Type
		} // for SoundData
	} // IsValid SoundTable
}

// Play Jump Sound
// OwnerCharacter의 위치에서 JumpSound를 Play
void UCSoundComponent::PlayJumpSound() const
{
	if (SoundData->Jump != nullptr && IsValid(GetOwner<ACBaseCharacter>()))
	{
		CLog::Log("Play Jump Sound");
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), SoundData->Jump, GetOwner<ACBaseCharacter>()->GetActorLocation(), GetOwner<ACBaseCharacter>()->GetActorRotation());
	}
	else
	{
		CLog::Log("Play Jump Sound nullptr");
	}
}
// Play Land Sound
// OwnerCharacter의 위치에서 LandSound를 Play
void UCSoundComponent::PlayLandSound() const
{
	if (SoundData->Land != nullptr && IsValid(GetOwner<ACBaseCharacter>()))
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), SoundData->Land, GetOwner<ACBaseCharacter>()->GetActorLocation(), GetOwner<ACBaseCharacter>()->GetActorRotation());
	}
	else
	{
		CLog::Log("Play Jump Sound nullptr");
	}
}
// Play Evade Sound
// OwnerCharacter의 위치에서 EvadeSound를 Play
void UCSoundComponent::PlayEvadeSound() const
{
	if (SoundData->Evade != nullptr && IsValid(GetOwner<ACBaseCharacter>()))
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), SoundData->Evade, GetOwner<ACBaseCharacter>()->GetActorLocation(), GetOwner<ACBaseCharacter>()->GetActorRotation());
	}
}

void UCSoundComponent::PlayAttackSound() const
{
	if (SoundData->Attack != nullptr && IsValid(GetOwner<ACBaseCharacter>()))
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), SoundData->Attack, GetOwner<ACBaseCharacter>()->GetActorLocation(), GetOwner<ACBaseCharacter>()->GetActorRotation());
	}
}

void UCSoundComponent::PlayHitSound() const
{
	if (SoundData->Hit != nullptr && IsValid(GetOwner<ACBaseCharacter>()))
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), SoundData->Hit, GetOwner<ACBaseCharacter>()->GetActorLocation(), GetOwner<ACBaseCharacter>()->GetActorRotation());
	}
}

void UCSoundComponent::PlayDeadSound() const
{
	if (SoundData->Dead != nullptr && IsValid(GetOwner<ACBaseCharacter>()))
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), SoundData->Dead, GetOwner<ACBaseCharacter>()->GetActorLocation(), GetOwner<ACBaseCharacter>()->GetActorRotation());
	}
}



