#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "Net/UnrealNetwork.h"
#include "CAttributeSet.generated.h"

// AttributeSet 클래스에서 사용할 매크로
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class ACTIONRPGGAME_API UCAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UCAttributeSet();
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// 현재 체력
	UPROPERTY(BlueprintReadOnly, Category="Health")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UCAttributeSet, Health);

	// 최대 체력
	UPROPERTY(BlueprintReadOnly, Category="Health")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UCAttributeSet, MaxHealth);

	// 현재 마나
	UPROPERTY(BlueprintReadOnly, Category="Mana")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UCAttributeSet, Mana);

	// 최대 마나
	UPROPERTY(BlueprintReadOnly, Category="Mana")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UCAttributeSet, MaxMana);

	// 현재 스테미너
	UPROPERTY(BlueprintReadOnly, Category="Stamina")
	FGameplayAttributeData Stamina;
	ATTRIBUTE_ACCESSORS(UCAttributeSet, Stamina);

	// 최대 스테미너
	UPROPERTY(BlueprintReadOnly, Category="MaxStamina")
	FGameplayAttributeData MaxStamina;
	ATTRIBUTE_ACCESSORS(UCAttributeSet, MaxStamina);

	// 걷기 속도
	UPROPERTY(BlueprintReadOnly, Category="Speed")
	FGameplayAttributeData WalkSpeed;
	ATTRIBUTE_ACCESSORS(UCAttributeSet, WalkSpeed);

	// 뛰기 속도
	UPROPERTY(BlueprintReadOnly, Category="Speed")
	FGameplayAttributeData RunSpeed;
	ATTRIBUTE_ACCESSORS(UCAttributeSet, RunSpeed);

protected:
	UFUNCTION()
	virtual void OnRep_Health(const FGameplayAttributeData& InValue);

	UFUNCTION()
	virtual void OnRep_MaxHealth(const FGameplayAttributeData& InValue);

	UFUNCTION()
	virtual void OnRep_Mana(const FGameplayAttributeData& InValue);

	UFUNCTION()
	virtual void OnRep_MaxMana(const FGameplayAttributeData& InValue);

	UFUNCTION()
	virtual void OnRep_Stamina(const FGameplayAttributeData& InValue);

	UFUNCTION()
	virtual void OnRep_MaxStamina(const FGameplayAttributeData& InValue);

	UFUNCTION()
	virtual void OnRep_WalkSpeed(const FGameplayAttributeData& InValue);

	UFUNCTION()
	virtual void OnRep_RunSpeed(const FGameplayAttributeData& InValue);

};
