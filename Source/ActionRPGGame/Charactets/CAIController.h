#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Components/CBehaviorComponent.h"
#include "CAIController.generated.h"

UCLASS()
class ACTIONRPGGAME_API ACAIController : public AAIController
{
	GENERATED_BODY()

public:
	// 생성자
	ACAIController();

	UFUNCTION(Category = "Getter")
	UBehaviorTree* GetBehaviorTree() const { return BehaviorTree; }

protected:
	virtual void OnPossess(APawn* InPawn) override;
	
	virtual void OnUnPossess() override;

	UPROPERTY(VisibleDefaultsOnly, Category = "Component")
	UCBehaviorComponent* Behavior;

	UPROPERTY(VisibleDefaultsOnly, Category = "Component")
	UAIPerceptionComponent* Perception;

	// BehaviorTree
	UPROPERTY(VisibleDefaultsOnly, Category = "BehaviorTree")
	UBehaviorTree* BehaviorTree;

};
