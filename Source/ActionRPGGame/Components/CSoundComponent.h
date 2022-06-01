#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "CSoundComponent.generated.h"

// 전방 선언
enum class EModelType : uint8;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ACTIONRPGGAME_API UCSoundComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// 생성자
	UCSoundComponent();

	// Jump Sound Play
	UFUNCTION(Category = "PlaySound")
	void PlayJumpSound();
	// Land Sound Play
	UFUNCTION(Category = "PlaySound")
	void PlayLandSound();
	// Evade Sound Play
	UFUNCTION(Category = "PlaySound")
	void PlayEvadeSound();

protected:
	// BeginPlay
	virtual void BeginPlay() override;

	UPROPERTY(VisibleDefaultsOnly, Category = "DataTable")
	UDataTable* SoundTable; // 데이터 테이블
private:
	UPROPERTY()
	class ACBaseCharacter* OwnerCharacter; // Owner Character
	struct FSoundData* SoundData; // 사운드 데이터
};
