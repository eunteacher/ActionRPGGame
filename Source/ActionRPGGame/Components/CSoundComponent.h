#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CSoundComponent.generated.h"

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

private:
	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundBase* Jump;
	// 착지
	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundBase* Land;
	// 피하기
	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundBase* Evade;
	// 전투
	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundBase* Attack;

	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundBase* Hit;

	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundBase* Dead;

	
};
