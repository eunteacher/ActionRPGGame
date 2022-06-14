#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPatrolPath.generated.h"

// 전방 선언
class USplineComponent;

UCLASS()
class ACTIONRPGGAME_API ACPatrolPath : public AActor
{
	GENERATED_BODY()
	
public:
	// 생성자
	ACPatrolPath();

	void AddSplinePoint(FVector InPointLocation);
	USplineComponent* GetSpline() const;

protected:
	UPROPERTY(VisibleDefaultsOnly, Category = "Component")
	USceneComponent* Root;

	UPROPERTY(VisibleDefaultsOnly, Category = "Component")
	USplineComponent* Spline;
};
