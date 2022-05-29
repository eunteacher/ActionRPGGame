#pragma once

#include "CoreMinimal.h"
#include "Abilites/CAttributeSet.h"
#include "GameFramework/Character.h"
#include "CBaseCharacter.generated.h"

// 전방 선언
enum class ESpeedType : uint8;

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

	// 캐릭터의 최대 스피드 값을 설정
	UFUNCTION(Category = "Character Speed")
	void SetMaxSpeed(ESpeedType InSpeed);

	// 현재 SpeedType을 반환
	UFUNCTION(Category = "Character Speed")
	ESpeedType GetCurrentSpeedType() { return SpeedType; }

protected:
	// BeginPlay 함수
	virtual void BeginPlay() override;
	// Land 함수
	virtual void Landed(const FHitResult& Hit) override;

	// 왼발, 오른발 표면을 검사하여 표면에 맞는 사운드를 Play
	UPROPERTY(VisibleDefaultsOnly, Category = "Component")
	class UCFootStepSoundComponent* FootStepSound; // FootStepSound 컴포넌트

	// 캐릭터의 Sound Play를 담당
	UPROPERTY(VisibleDefaultsOnly, Category = "Component")
	class UCSoundComponent* Sound; // SoundComponent 컴포넌트 

	// 몽타주 Play를 담당
	UPROPERTY(VisibleDefaultsOnly, Category = "Component")
	class UCMontageComponent* Montage; // MontageComponent 컴포넌트

	// 액터가 어빌리티를 사용하기 위해 AbilitySystemComponent에 어빌리티를 부여하고, 접근을 허용
	UPROPERTY(VisibleDefaultsOnly, Category = "Component")
	class UCAbilitySystemComponent* AbilitySystem; // AbilitySystem 컴포넌트 

	// UCAttribute 클래스에서 호출된다. Player와 Monster Character에 내용을 정의한다.
	virtual void OnHealthChanged(const FGameplayTagContainer& EventTags);
	virtual void OnManaChanged(const FGameplayTagContainer& EventTags);
	virtual void OnStaminaChanged(const FGameplayTagContainer& EventTags);
	virtual void OnWalkSpeedChanged(const FGameplayTagContainer& EventTags);
	virtual void OnRunSpeedChanged(const FGameplayTagContainer& EventTags);

	// friend 선언
	friend UCAttributeSet;

	// 어빌리티 시스템에 의해 수정된 Attribute 값을 가져오기 위해 선언
	UPROPERTY(VisibleDefaultsOnly, Category = "AbilitySystem")
	UCAttributeSet* AttributeSet; // AttributeSet

	// Speed Type
	UPROPERTY(EditAnywhere, Category = "Type")
	ESpeedType SpeedType;
};
