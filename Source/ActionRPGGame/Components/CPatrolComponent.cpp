#include "Components/CPatrolComponent.h"

UCPatrolComponent::UCPatrolComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UCPatrolComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UCPatrolComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}
