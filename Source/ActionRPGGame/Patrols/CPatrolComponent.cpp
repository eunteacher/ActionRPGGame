#include "Patrols/CPatrolComponent.h"
#include "ActionRPGGame.h"
#include "Characters/CBaseCharacter.h"
#include "Components/SplineComponent.h"
#include "Patrols/CPatrolPath.h"
#include "Types/CEnumTypes.h"

UCPatrolComponent::UCPatrolComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	// 멤버 변수 초기화
	PatrolType = EPatrolType::None;
	PathIndex = 0;
	Radius = 50.0f;
	SplinePointOffset = 500.0f;

	// PatrolPathClass 클래스를 가져와 저장
	// Blueprint'/Game/Enemy/Blueprints/BP_CPatrolPath.BP_CPatrolPath'
	ConstructorHelpers::FClassFinder<ACPatrolPath> patrolPathBlueprintClass(TEXT("Blueprint'/Game/Enemy/Blueprints/BP_CPatrolPath.BP_CPatrolPath_C'"));
	if(patrolPathBlueprintClass.Succeeded())
	{
		PatrolPathClass = patrolPathBlueprintClass.Class;
	}
}

void UCPatrolComponent::BeginPlay()
{
	Super::BeginPlay();

	// PatrolType이 None일 경우 PatrolPath를 생성하지 않는다.
	if(PatrolType != EPatrolType::None)
	{
		FTransform transform = GetOwner<ACBaseCharacter>()->GetTransform();
		transform.SetLocation(FVector(transform.GetLocation().X, transform.GetLocation().Y, transform.GetLocation().Z - 90.0f));
		PatrolPath = GetWorld()->SpawnActorDeferred<ACPatrolPath>(PatrolPathClass, transform, GetOwner<ACBaseCharacter>());
		UGameplayStatics::FinishSpawningActor(PatrolPath, transform);

		switch (PatrolType)
		{
		case EPatrolType::Line:
			{
				FVector location = PatrolPath->GetActorLocation() + PatrolPath->GetActorForwardVector() * SplinePointOffset;
				PatrolPath->AddSplinePoint(location);
			}
			break;
		case EPatrolType::Triangle:
			break;
		case EPatrolType::Square:
			break;
		case EPatrolType::Max:
			break;
		default: ;
		}
		
	}
}

void UCPatrolComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UCPatrolComponent::UpdateNextPath()
{
	// 전체 SplinePoint의 개수를 가져온다.
	const int32 splineCount = PatrolPath->GetSpline()->GetNumberOfSplinePoints();

	if(PathIndex >= splineCount - 1)
	{
		PathIndex = 0;
	}
	else
	{
		PathIndex++;
	}
}

FVector UCPatrolComponent::GetPointLocation()
{
	return PatrolPath->GetSpline()->GetLocationAtSplinePoint(PathIndex, ESplineCoordinateSpace::World);
}

float UCPatrolComponent::GetRadius()
{
	return Radius;
}

bool UCPatrolComponent::CanPatorl()
{
	return PatrolType != EPatrolType::None ? true : false;
}

