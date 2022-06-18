#include "Components/CSoundComponent.h"
#include "ActionRPGGame.h"
#include "CGameInstance.h"
#include "Characters/CBaseCharacter.h"
// #include "Types/CEnumTypes.h"

// 생성자
UCSoundComponent::UCSoundComponent()
{
	
}

// BeginPlay
void UCSoundComponent::BeginPlay()
{
	Super::BeginPlay();

	// GameInstance에서 데이터 테이블 읽어오기
	if (IsValid(GetOwner<ACBaseCharacter>()->GetGameInstance<UCGameInstance>()))
	{
		UDataTable* soundTable = GetOwner<ACBaseCharacter>()->GetGameInstance<UCGameInstance>()->ReadSoundTable();

		if (IsValid(soundTable))
		{
			TArray<FSoundData*> soundDatas;
			soundTable->GetAllRows<FSoundData>("", soundDatas);

			for (FSoundData* soundData : soundDatas)
			{
				if (soundData->Type == GetOwner<ACBaseCharacter>()->GetModelType())
				{
					Jump = soundData->Jump;
					Land = soundData->Land;
					Evade = soundData->Evade;
					Attack = soundData->Attack;
					Hit = soundData->Hit;
					Dead = soundData->Dead;
				} // if type
			} // for SoundData
		} 
	}
}

// Play Jump Sound
// OwnerCharacter의 위치에서 JumpSound를 Play
void UCSoundComponent::PlayJumpSound() const
{
	if (Jump != nullptr && IsValid(GetOwner<ACBaseCharacter>()))
	{
		CLog::Log("Play Jump Sound");
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), Jump, GetOwner<ACBaseCharacter>()->GetActorLocation(), GetOwner<ACBaseCharacter>()->GetActorRotation());
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
	if (Land != nullptr && IsValid(GetOwner<ACBaseCharacter>()))
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), Land, GetOwner<ACBaseCharacter>()->GetActorLocation(), GetOwner<ACBaseCharacter>()->GetActorRotation());
	}
}

// Play Evade Sound
// OwnerCharacter의 위치에서 EvadeSound를 Play
void UCSoundComponent::PlayEvadeSound() const
{
	if (Evade != nullptr && IsValid(GetOwner<ACBaseCharacter>()))
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), Evade, GetOwner<ACBaseCharacter>()->GetActorLocation(), GetOwner<ACBaseCharacter>()->GetActorRotation());
	}
}

void UCSoundComponent::PlayAttackSound() const
{
	if (Attack != nullptr && IsValid(GetOwner<ACBaseCharacter>()))
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), Attack, GetOwner<ACBaseCharacter>()->GetActorLocation(), GetOwner<ACBaseCharacter>()->GetActorRotation());
	}
}

void UCSoundComponent::PlayHitSound() const
{
	if (Hit != nullptr && IsValid(GetOwner<ACBaseCharacter>()))
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), Hit, GetOwner<ACBaseCharacter>()->GetActorLocation(), GetOwner<ACBaseCharacter>()->GetActorRotation());
	}
}

void UCSoundComponent::PlayDeadSound() const
{
	if (Dead != nullptr && IsValid(GetOwner<ACBaseCharacter>()))
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), Dead, GetOwner<ACBaseCharacter>()->GetActorLocation(), GetOwner<ACBaseCharacter>()->GetActorRotation());
	}
}



