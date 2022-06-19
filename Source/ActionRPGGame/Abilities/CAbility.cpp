#include "CAbility.h"
#include "ActionRPGGame.h"
#include "CGameInstance.h"
#include "Characters/CBaseCharacter.h"
#include "Characters/CPlayerController.h"
#include "Weapon/CWeapon.h"

// 생성자
ACAbility::ACAbility()
{
	PrimaryActorTick.bCanEverTick = true;

	IsAvailable = true;
	IsActivation = false;

	DrawDebugType = EDrawDebugTrace::ForOneFrame;
	TraceType = ETraceTypeQuery::TraceTypeQuery2;
}

void ACAbility::InitAbility(ACBaseCharacter* InOwnerCharacter, ACWeapon* InOwnerWeapon)
{
	OwnerCharacter = InOwnerCharacter;
	OwnerWeapon = InOwnerWeapon;
}

void ACAbility::OnActivation()
{
	CLog::Log("ACAbility OnActivation");
}

void ACAbility::OnProgress()
{
	CLog::Log("ACAbility OnProgress");
}

void ACAbility::OnDeActivation()
{
	CLog::Log("ACAbility OnDeActivation");
}

void ACAbility::SetIsAvailable(bool InIsAvailable)
{
	CLog::Print(FString("SetIsAvailable"));
	IsAvailable = InIsAvailable;
}

void ACAbility::SpawnDamageText(FVector InLocation, ACBaseCharacter* InHitCharacter, float InDamage, bool InIsDamageEffect)
{
	GetGameInstance<UCGameInstance>()->SpawnDamageText(InLocation, InHitCharacter, InDamage, InIsDamageEffect);
}

