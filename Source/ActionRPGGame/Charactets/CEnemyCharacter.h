#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Charactets/CBaseCharacter.h"
#include "CEnemyCharacter.generated.h"

// 전방선언
class ACDamageText;
class UWidgetComponent;

UCLASS()
class ACTIONRPGGAME_API ACEnemyCharacter : public ACBaseCharacter
{
	GENERATED_BODY()
public:
	// 생성자
	ACEnemyCharacter();
	// TakeDamage
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	
	UFUNCTION(Category = "Getter")
	uint8 GetTeamID() const { return TeamID; }

protected:
	// BeginPlay
	virtual void BeginPlay() override;

	// TeamID
	UPROPERTY(VisibleDefaultsOnly, Category = "AI")
	uint8 TeamID;

	UPROPERTY(VisibleDefaultsOnly,Category = "Component")
	UWidgetComponent* HealthBarWidget;

	
};
