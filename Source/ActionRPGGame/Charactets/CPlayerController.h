#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Engine/DataTable.h"
#include "CPlayerController.generated.h"

UCLASS()
class ACTIONRPGGAME_API ACPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	// 생성자
	ACPlayerController();

	// Tick
	virtual void Tick(float DeltaSeconds) override;

protected:
	// Begin Play
	virtual void BeginPlay() override;
	
	// Status 데이터 테이블
	UPROPERTY(EditDefaultsOnly, Category = "DataTable")
	UDataTable* StatusDataTable;

	// 체력
	UPROPERTY(EditAnywhere, Category = "Status")
	float Health;

	// 최대 체력
	UPROPERTY(EditAnywhere, Category = "Status")
	float MaxHealth;

	// 마나
	UPROPERTY(EditAnywhere, Category = "Status")
	float Mana;

	// 최대 마나
	UPROPERTY(EditAnywhere, Category = "Status")
	float MaxMana;

	// 스테미너
	UPROPERTY(EditAnywhere, Category = "Status")
	float Stamina;

	// 최대 스테미너
	UPROPERTY(EditAnywhere, Category = "Status")
	float MaxStamina;
	
private:
	// Health 값 더하기
	void AddHealth(float InValue);
	// Health 값 빼기
	void SubtractHealth(float InValue);
	// Mana 값 더하기
	void AddMana(float InValue);
	// Mana 값 빼기
	void SubtractMana(float InValue);
	// Stamina 값 더하기
	void AddStamina(float InValue);
	// Stamina 값 빼기
	void SubtractStamina(float InValue);
	
	// 델리게이트로 호출
	// Health가 변할 경우 호출
	UFUNCTION()
	void OnHealthChanged(float InHealth, float InMaxHealth);
	// Mana가 변할 경우 호출
	UFUNCTION()
	void OnManaChanged(float InMana, float InMaxMana);
	// Stamina가 변할 경우 호출
	UFUNCTION()
	void OnStaminaChanged(float InStamina, float InMaxStamina);
};
