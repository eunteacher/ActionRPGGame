#include "CAbility.h"
#include "ActionRPGGame.h"
#include "Characters/CBaseCharacter.h"
#include "Characters/CPlayerController.h"
#include "Weapon/CWeapon.h"

// 생성자
ACAbility::ACAbility()
{
	PrimaryActorTick.bCanEverTick = true;

	IsAvailable = true;
	IsActivation = false;
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

void ACAbility::OnNotify()
{
	CLog::Log("ACAbility OnNotify");
}

void ACAbility::OnDeActivation()
{
	CLog::Log("ACAbility OnDeActivation");
}

void ACAbility::SetIsAvailable(bool InIsAvailable)
{
	IsAvailable = InIsAvailable;
	CLog::Print(FString("SetIsAvailable"));
}

