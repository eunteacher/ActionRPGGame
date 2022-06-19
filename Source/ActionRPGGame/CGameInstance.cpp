#include "CGameInstance.h"

#include "Characters/CBaseCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetTextLibrary.h"
#include "Widgets/CDamageText.h"

UCGameInstance::UCGameInstance()
{
	// Sound Data Table
	// DataTable'/Game/DataTables/DT_Sound.DT_Sound'
	static ConstructorHelpers::FObjectFinder<UDataTable> SoundTableAsset(TEXT("DataTable'/Game/DataTables/DT_Sound.DT_Sound'"));
	if (SoundTableAsset.Succeeded())
	{
		SoundTable = SoundTableAsset.Object;
	}

	// Montage Data Table
	// DataTable'/Game/DataTables/DT_Montage.DT_Montage'
	static ConstructorHelpers::FObjectFinder<UDataTable> MontageTableAsset(TEXT("DataTable'/Game/DataTables/DT_Montage.DT_Montage'"));
	if (MontageTableAsset.Succeeded())
	{
		MontageTable = MontageTableAsset.Object;
	}

	// DataTable'/Game/DataTables/DT_FootStepSound.DT_FootStepSound'
	static ConstructorHelpers::FObjectFinder<UDataTable> FootStepSoundTableAsset(TEXT("DataTable'/Game/DataTables/DT_FootStepSound.DT_FootStepSound'"));
	if (FootStepSoundTableAsset.Succeeded())
	{
		FootStepSoundTable = FootStepSoundTableAsset.Object;
	}

	// Status 데이터 테이블 에셋을 가져와 저장
	// DataTable'/Game/DataTables/DT_Status.DT_Status'
	const ConstructorHelpers::FObjectFinder<UDataTable> statusTableAsset(TEXT("DataTable'/Game/DataTables/DT_Status.DT_Status'"));
	if (statusTableAsset.Succeeded())
	{
		StatusTable = statusTableAsset.Object;
	}

	// Blueprint'/Game/Widgets/Blueprints/BP_CDamageText.BP_CDamageText'
	ConstructorHelpers::FClassFinder<ACDamageText> damageTextClass(TEXT("Blueprint'/Game/Widgets/Blueprints/BP_CDamageText.BP_CDamageText_C'"));
	if(damageTextClass.Succeeded())
	{
		DamageTextClass = damageTextClass.Class;
	}
}

void UCGameInstance::SpawnDamageText(FVector InLocation, ACBaseCharacter* InHitCharacter, float InDamage, bool InIsDamageEffect)
{
	// Spawn DamageText 
	FTransform transform;
	transform.SetLocation(InLocation);
	ACDamageText* damageText = GetWorld()->SpawnActorDeferred<ACDamageText>(DamageTextClass, transform, InHitCharacter);
	UGameplayStatics::FinishSpawningActor(damageText, transform);
	bool isPlayer = InHitCharacter->GetStatusType() == EStatusType::Player ? true : false;
	damageText->SetDamageText(UKismetTextLibrary::Conv_FloatToText(InDamage, ERoundingMode::HalfFromZero), isPlayer, InIsDamageEffect);
}

TSubclassOf<ACDamageText> UCGameInstance::GetDamageTextClass()
{
	return DamageTextClass;
}

UDataTable* UCGameInstance::ReadSoundTable()
{
	return SoundTable;
}

UDataTable* UCGameInstance::ReadMontageTable()
{
	return MontageTable;
}

UDataTable* UCGameInstance::ReadFootStepSoundTable()
{
	return FootStepSoundTable;
}

UDataTable* UCGameInstance::ReadStatusTable()
{
	return StatusTable;
}
