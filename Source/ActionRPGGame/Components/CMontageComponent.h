#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "Types/CDataTableType.h"
#include "CMontageComponent.generated.h"

// 전방 선언
enum class EMontageType : uint8;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ACTIONRPGGAME_API UCMontageComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// 생성자
	UCMontageComponent();
	// 몽타주 실행
	void PlayMontage(const EModelType InModel, const EMontageType InMontage);

protected:
	// BeingPlay
	virtual void BeginPlay() override;

	UPROPERTY(VisibleDefaultsOnly, Category = "DataTable")
	UDataTable* MontageTable; // 데이터 테이블

private:
	TMap<EModelType, TArray<FMontageData*>> MontageDataMaps; // 몽타주 데이터 Map
};
