#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CBaseCharacter.generated.h"

// 전방 선언
enum class EModelType : uint8;
enum class ESpeedType : uint8;
enum class EStateType : uint8;

// 기본 캐릭터 클래스
// Player와 Monster 모두 이 클래스를 상속 받는다.
UCLASS()
class ACTIONRPGGAME_API ACBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// 생성자
	ACBaseCharacter();
	// Tick 함수
	virtual void Tick(float DeltaTime) override;
	// SetupPlayerInputComponent 
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// 캐릭터의 StateType 설정
	UFUNCTION(Category = "Character Speed")
	void SetState(EStateType InType);
	// 캐릭터의 최대 스피드 값을 설정
	UFUNCTION(Category = "Character Speed")
	void SetMaxSpeed(ESpeedType InSpeed);
	
	// 현재 StateType을 반환
	UFUNCTION(Category = "Character State")
	EStateType GetCurrentStateType() const { return StateType; }
	// 현재 SpeedType을 반환
	UFUNCTION(Category = "Character Speed")
	ESpeedType GetCurrentSpeedType() const { return SpeedType; }
	// ModelType을 반환
	UFUNCTION(Category = "Character Speed")
	EModelType GetCurrentModelType() const { return ModelType; }

protected:
	// BeginPlay 함수
	virtual void BeginPlay() override;
	// Land 함수
	virtual void Landed(const FHitResult& Hit) override;

	// 왼발, 오른발 표면을 검사하여 표면에 맞는 사운드를 Play
	UPROPERTY(VisibleDefaultsOnly, Category = "Component")
	class UCFootStepSoundComponent* FootStepSound; // FootStep 컴포넌트

	// 캐릭터의 Sound Play를 담당
	UPROPERTY(VisibleDefaultsOnly, Category = "Component")
	class UCSoundComponent* Sound; // Sound 컴포넌트 

	// 몽타주 Play를 담당
	UPROPERTY(VisibleDefaultsOnly, Category = "Component")
	class UCMontageComponent* Montage; // Montage 컴포넌트

	// Speed Type
	UPROPERTY(VisibleDefaultsOnly, Category = "Type")
	ESpeedType SpeedType;
	// StateType
	UPROPERTY(VisibleDefaultsOnly, Category = "Type")
	EStateType StateType;
	// ModelType
	UPROPERTY(VisibleDefaultsOnly, Category = "Type")
	EModelType ModelType;
};
