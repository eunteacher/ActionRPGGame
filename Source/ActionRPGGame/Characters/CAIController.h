#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CAIController.generated.h"

// 전방 선언
class ACBaseCharacter;

UCLASS()
class ACTIONRPGGAME_API ACAIController : public AAIController
{
	GENERATED_BODY()

public:
	// 생성자
	ACAIController();

protected:
	virtual void BeginPlay() override;

	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

	UPROPERTY(VisibleDefaultsOnly, Category = "Component")
	UAIPerceptionComponent* Perception;

	// BehaviorTree
	UPROPERTY(VisibleDefaultsOnly, Category = "AI Asset")
	UBehaviorTree* BehaviorTree;

	UPROPERTY(VisibleDefaultsOnly, Category = "AI Asset")
	UBlackboardData* BlackboardData;

	UPROPERTY()
	class UAISenseConfig_Sight* Sight;

	UPROPERTY()
	ACBaseCharacter* OwnerCharacter;

};
