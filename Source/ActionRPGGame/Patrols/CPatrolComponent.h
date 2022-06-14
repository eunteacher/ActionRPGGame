#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CPatrolComponent.generated.h"

// 전방 선언
class ACPatrolPath;
enum class EPatrolType : uint8;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONRPGGAME_API UCPatrolComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// 생성자
	UCPatrolComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// 다음 경로를 지정한다.
	void UpdateNextPath();

	// 현재 Spline Point의 World 위치를 반환
	FVector GetPointLocation();

	// 접근 반경을 반환
	float GetRadius();

	// Patrol Type을 확인하여 Patrol의 가능 여부를 판단
	bool CanPatorl();
protected:
	// BeginPlay
	virtual void BeginPlay() override;

	// Patrol Type, Blueprint에서 설정
	UPROPERTY(EditAnywhere, Category = "Patrol")
	EPatrolType PatrolType;
	
	// PatrolPath를 담고 있는 Actor 클래스
	UPROPERTY(VisibleDefaultsOnly, Category = "Patrol")
	TSubclassOf<ACPatrolPath> PatrolPathClass;

	// PatrolPath가 가지고 있는 Spline 인덱스
	UPROPERTY(VisibleDefaultsOnly, Category = "Patrol")
	int32 PathIndex;

	// Spline 포인트에 도달 Radius 거리
	UPROPERTY(VisibleDefaultsOnly, Category = "Patrol")
	float Radius;

	// Spline 포인트에 도달 Offset 거리
	UPROPERTY(VisibleDefaultsOnly, Category = "Patrol")
	float SplinePointOffset;

	
private:
	UPROPERTY()
	ACPatrolPath* PatrolPath;
};
