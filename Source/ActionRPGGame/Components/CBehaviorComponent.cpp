#include "Components/CBehaviorComponent.h"

UCBehaviorComponent::UCBehaviorComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCBehaviorComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UCBehaviorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

