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

	// Setter
	// ModelType을 매개변수로 받는다.
	void SetModelType(EModelType InType) { ModelType = InType; }
protected:
	// BeginPlay
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "DataTable")
	UDataTable* SoundTable; // 데이터 테이블

	// 모델 타입은 Character 생성자에서 정의
	UPROPERTY(EditAnywhere, Category = "Type")
	EModelType ModelType; // 캐릭터 모델 타입

private:
	UPROPERTY()
	ACharacter* OwnerCharacter; // Owner Character

	struct FSoundData* SoundData; // 사운드 데이터
};
