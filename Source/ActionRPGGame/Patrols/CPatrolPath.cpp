#include "Patrols/CPatrolPath.h"
#include "Components/SplineComponent.h"

// Sets default values
ACPatrolPath::ACPatrolPath()
{
	PrimaryActorTick.bCanEverTick = true;

	// Scene 컴포넌트 생성 및 초기화
	Root = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(Root);
	// Spline 컴포넌트 생성 및 초기화
	Spline = CreateDefaultSubobject<USplineComponent>("Spline");
	Spline->SetupAttachment(Root);
	Spline->SetClosedLoop(true);
}

// Add Spline Point
void ACPatrolPath::AddSplinePoint(FVector InPointLocation)
{
	Spline->AddSplineWorldPoint(InPointLocation);
}

USplineComponent* ACPatrolPath::GetSpline() const
{
	return Spline;
}


