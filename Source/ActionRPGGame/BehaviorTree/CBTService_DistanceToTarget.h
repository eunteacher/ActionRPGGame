#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "CBTService_DistanceToTarget.generated.h"

UCLASS()
class ACTIONRPGGAME_API UCBTService_DistanceToTarget : public UBTService
{
	GENERATED_BODY()

public:
	UCBTService_DistanceToTarget();
protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

};
