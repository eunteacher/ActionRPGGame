#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Characters/CBaseCharacter.h"
#include "CEnemyCharacter.generated.h"

// 전방선언
class ACDamageText;
class UWidgetComponent;
class UCPatrolComponent;

UCLASS()
class ACTIONRPGGAME_API ACEnemyCharacter : public ACBaseCharacter
{
	GENERATED_BODY()
public:
	// 생성자
	ACEnemyCharacter();
	// TakeDamage
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	virtual void OnDead() override;
protected:
	// BeginPlay
	virtual void BeginPlay() override;

	UPROPERTY(VisibleDefaultsOnly,Category = "Component")
	UWidgetComponent* HealthBarWidget;

	UPROPERTY(VisibleDefaultsOnly,Category = "Component")
	UCPatrolComponent* Patrol;

	
};
