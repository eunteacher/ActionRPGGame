#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Types/CStructTypes.h"
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
	void PlayMontage(const EMontageType InMontageType);

protected:
	// BeingPlay
	virtual void BeginPlay() override;

private:
	TMap<EMontageType, FUseMontageData> UseMontageDataMaps; // Montage Data Maps
};
