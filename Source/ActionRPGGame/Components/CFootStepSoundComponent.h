#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Types/CDataTableType.h"
#include "CFootStepSoundComponent.generated.h"

// 전방 선언
enum class ESpeedType : uint8;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ACTIONRPGGAME_API UCFootStepSoundComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// 생성자
	UCFootStepSoundComponent();

	UPROPERTY(EditAnywhere, Category = "SocketName")
	FName LeftFoot; // 왼쪽 발 소켓 이름

	UPROPERTY(EditAnywhere, Category = "SocketName")
	FName RightFoot; // 오른쪽 발 소켓 이름

	UPROPERTY(EditAnywhere, Category = "Trace")
	TEnumAsByte<ETraceTypeQuery> TraceType; // 트레이스 타입 

	UPROPERTY(EditAnywhere, Category = "Trace")
	TEnumAsByte<EDrawDebugTrace::Type> DrawDebugType; // 디버그 타입

	// 노티파이를 통해서 호출된다.
	// 왼발 Sound Play
	UFUNCTION()
	void NotifyLeftFootStep(const ESpeedType InType);
	// 오른발 Sound Play
	UFUNCTION()
	void NotifyRightFootStep(const ESpeedType InType);

protected:
	// BeginPlay
	virtual void BeginPlay() override;
	// 지면을 검사하고, 지면에 맞는 사운드를 플레이
	void PlayFootStepSound(const ESpeedType InType, const bool IsRight);
	
private:
	TArray<FFootStepSoundData* > FootStepSoundData; // FootStepSound 데이터 TArray
};
