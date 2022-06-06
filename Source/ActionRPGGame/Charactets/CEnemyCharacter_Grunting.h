#pragma once

#include "CoreMinimal.h"
#include "Charactets/CEnemyCharacter.h"
#include "CEnemyCharacter_Grunting.generated.h"

UCLASS()
class ACTIONRPGGAME_API ACEnemyCharacter_Grunting : public ACEnemyCharacter
{
	GENERATED_BODY()
public:
	// 생성자
	ACEnemyCharacter_Grunting();

protected:
	// BeginPlay
	virtual void BeginPlay() override;
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	
};
