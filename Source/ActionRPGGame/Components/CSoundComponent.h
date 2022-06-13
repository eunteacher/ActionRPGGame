#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Types/CDataTableType.h"
#include "CSoundComponent.generated.h"

// 전방 선언
enum class EWeaponType : uint8;
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
	void PlayJumpSound() const;
	// Land Sound Play
	UFUNCTION(Category = "PlaySound")
	void PlayLandSound() const;
	// Evade Sound Play
	UFUNCTION(Category = "PlaySound")
	void PlayEvadeSound() const;

	UFUNCTION(Category = "PlaySound")
	void PlayAttackSound() const;

	UFUNCTION(Category = "PlaySound")
	void PlayHitSound() const;

	UFUNCTION(Category = "PlaySound")
	void PlayDeadSound() const;

protected:
	// BeginPlay
	virtual void BeginPlay() override;

	// Sound 컴포넌트에서 사용할 Sound Data Table
	UPROPERTY(VisibleDefaultsOnly, Category = "DataTable")
	UDataTable* SoundTable;

private:
	FSoundData* SoundData; // 사운드 데이터
};
