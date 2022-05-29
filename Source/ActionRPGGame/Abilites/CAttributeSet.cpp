#include "Abilites/CAttributeSet.h"
#include "CAbilitySystemComponent.h"
#include "GameplayEffect.h"
#include "GameplayEffectExtension.h"
#include "Charactets/CBaseCharacter.h"
#include "Charactets/CPlayerController.h"
// 생성자
UCAttributeSet::UCAttributeSet()
{
	// 멤버 변수 초기화
	Health = 1.0f;
	MaxHealth = 1.0f;
	Mana = 1.0f;
	MaxMana = 1.0f;
	Stamina = 1.0f;
	MaxStamina = 1.0f;
	WalkSpeed = 1.0f;
	RunSpeed = 1.0f;
}

// Attribute에 대한 수정 직전 호출되는 함수
void UCAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
}

// Attribute의 값 수정 후 호출되는 함수
void UCAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	FGameplayEffectContextHandle context = Data.EffectSpec.GetContext();
	UAbilitySystemComponent* abilitySystemComponent = context.GetOriginalInstigatorAbilitySystemComponent();
	const FGameplayTagContainer& gameplayTagContainer = *Data.EffectSpec.CapturedSourceTags.GetAggregatedTags();

	AActor* targetActor = nullptr;
	AController* targetController = nullptr;
	ACBaseCharacter* targetCharacter = nullptr;
	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		targetActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		targetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		targetCharacter = Cast<ACBaseCharacter>(targetActor);
	}

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth()));

		if (targetCharacter)
		{
			targetCharacter->OnHealthChanged(gameplayTagContainer);
		}
	}
	else if (Data.EvaluatedData.Attribute == GetManaAttribute())
	{
		// Clamp mana
		SetMana(FMath::Clamp(GetMana(), 0.0f, GetMaxMana()));

		if (targetCharacter)
		{
			targetCharacter->OnManaChanged(gameplayTagContainer);
		}
	}
	else if (Data.EvaluatedData.Attribute == GetWalkSpeedAttribute())
	{
		if (targetCharacter)
		{
			targetCharacter->OnWalkSpeedChanged(gameplayTagContainer);
		}
	}
	else if (Data.EvaluatedData.Attribute == GetRunSpeedAttribute())
	{
		if (targetCharacter)
		{
			targetCharacter->OnRunSpeedChanged(gameplayTagContainer);
		}
	}
	
}

void UCAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UCAttributeSet, Health);
	DOREPLIFETIME(UCAttributeSet, MaxHealth);
	DOREPLIFETIME(UCAttributeSet, Mana);
	DOREPLIFETIME(UCAttributeSet, MaxMana);
	DOREPLIFETIME(UCAttributeSet, Stamina);
	DOREPLIFETIME(UCAttributeSet, MaxStamina);
	DOREPLIFETIME(UCAttributeSet, WalkSpeed);
	DOREPLIFETIME(UCAttributeSet, RunSpeed);
}

void UCAttributeSet::OnRep_Health(const FGameplayAttributeData& InValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCAttributeSet, Health, InValue);
}

void UCAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& InValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCAttributeSet, MaxHealth, InValue);
}

void UCAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& InValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCAttributeSet, MaxMana, InValue);
}

void UCAttributeSet::OnRep_MaxStamina(const FGameplayAttributeData& InValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCAttributeSet, MaxStamina, InValue);
}

void UCAttributeSet::OnRep_Mana(const FGameplayAttributeData& InValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCAttributeSet, Mana, InValue);
}

void UCAttributeSet::OnRep_Stamina(const FGameplayAttributeData& InValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCAttributeSet, Stamina, InValue);
}

void UCAttributeSet::OnRep_WalkSpeed(const FGameplayAttributeData& InValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCAttributeSet, WalkSpeed, InValue);
}

void UCAttributeSet::OnRep_RunSpeed(const FGameplayAttributeData& InValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCAttributeSet, RunSpeed, InValue);
}
