
#pragma once

#include "CoreMinimal.h"
#include "Characters/CBaseCharacter.h"
#include "GameFramework/Actor.h"
#include "Kismet/KismetSystemLibrary.h"
#include "CAbility.generated.h"

// 전방 선언
enum class EMontageType : uint8;
enum class EAbilityType : uint8;
class ACWeapon;

UCLASS()
class ACTIONRPGGAME_API ACAbility : public AActor
{
	GENERATED_BODY()
	
public:	
	ACAbility();
	
	// Ability를 사용 중인 Character와 Weapon 초기화
	void InitAbility(ACBaseCharacter* InOwnerCharacter, ACWeapon* InOwnerWeapon);
	void SetIsAvailable(bool InIsAvailable);
	void SpawnDamageText(FVector InLocation, ACBaseCharacter* InHitCharacter, float InDamage, bool InIsDamageEffect = false);

	// Ability 활성화
	virtual void OnActivation();

	// Notify 호출
	virtual void OnProgress();

	// Ability 비활성화
	virtual void OnDeActivation();
	
	EWeaponType GetWeaponType() const { return WeaponType; }
	EAbilityType GetAbilityType() const { return AbilityType; }

	UTexture2D* GetAbilityIcon() const { return AbilityIcon; }
	
	float GetManaCost() { return ManaCost; } // 어빌리티 마나 소모량
	int32 GetDuration() { return Duration; } // 어빌리티 지속 시간
	float GetCoolDown() { return CoolDown; } // 어빌리티 쿨다운
protected:
	UPROPERTY(EditAnywhere, Category = "Trace")
	TEnumAsByte<EDrawDebugTrace::Type> DrawDebugType;

	UPROPERTY(EditAnywhere, Category = "Trace")
	TEnumAsByte<ETraceTypeQuery> TraceType;

	UPROPERTY(VisibleDefaultsOnly, Category = "UserSetting")
	EWeaponType WeaponType; // 무기 타입

	UPROPERTY(VisibleDefaultsOnly, Category = "UserSetting")
	EAbilityType AbilityType; // 어빌리티 타입

	UPROPERTY(VisibleDefaultsOnly, Category = "UserSetting")
	EMontageType MontageType; // 어빌리티 몽타주 타입

	UPROPERTY(EditAnywhere, Category = "UserSetting")
	float Damage; // 어빌리티 데미지

	UPROPERTY(EditAnywhere, Category = "UserSetting")
	float CoolDown; // 어빌리티 쿨다운

	UPROPERTY(EditAnywhere, Category = "UserSetting")
	float ManaCost; // 어빌리티 마나 소모량

	UPROPERTY(EditAnywhere, Category = "UserSetting")
	int32 Duration; // 어빌리티 지속 시간

	UPROPERTY(EditAnywhere, Category = "UserSetting")
	UTexture2D* AbilityIcon; // 어빌리티의 Icon

	UPROPERTY()
	ACBaseCharacter* OwnerCharacter; // 사용 중인 캐릭터

	UPROPERTY()
	ACWeapon* OwnerWeapon; // 사용 중인 무기

	bool IsAvailable; // 어빌리티의 사용 가능 여부 
	bool IsActivation; // 어빌리티의 활성화 여부 
};
