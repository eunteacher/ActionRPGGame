#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Engine/GameInstance.h"
#include "CGameInstance.generated.h"

UCLASS()
class ACTIONRPGGAME_API UCGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UCGameInstance();

	void SpawnDamageText(FVector InLocation, class ACBaseCharacter* InHitCharacter, float InDamage, bool InIsDamageEffect = false);
	
	TSubclassOf<class ACDamageText> GetDamageTextClass();

	UDataTable* ReadSoundTable();
	UDataTable* ReadMontageTable();
	UDataTable* ReadFootStepSoundTable();
	UDataTable* ReadStatusTable();
protected:
	// Sound 컴포넌트에서 사용할 Sound Data Table
	UPROPERTY(VisibleDefaultsOnly, Category = "DataTable")
	UDataTable* SoundTable;

	// Montage 컴포넌트에서 사용할 Montage Data Table
	UPROPERTY(VisibleDefaultsOnly, Category = "DataTable")
	UDataTable* MontageTable;

	// FootStepSound 컴포넌트에서 사용할 FootStepSound Data Table
	UPROPERTY(VisibleDefaultsOnly, Category = "DataTable")
	UDataTable* FootStepSoundTable;

	// 캐릭터의 Status Data Table
	UPROPERTY(VisibleDefaultsOnly, Category = "DataTable")
	UDataTable* StatusTable;

	UPROPERTY(VisibleDefaultsOnly, Category = "UserSetting")
	TSubclassOf<ACDamageText> DamageTextClass;
};


