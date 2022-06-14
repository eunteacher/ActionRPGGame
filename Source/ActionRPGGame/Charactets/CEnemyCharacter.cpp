#include "Charactets/CEnemyCharacter.h"
#include "ActionRPGGame.h"
#include "Components/CapsuleComponent.h"
#include "Components/CMontageComponent.h"
#include "Components/CSoundComponent.h"
#include "Weapon/CWeapon_Base.h"
#include "Widgets/CUserWidget_BaseProgressBar.h"
#include "Components/WidgetComponent.h"

ACEnemyCharacter::ACEnemyCharacter()
{
	// TeamID 초기화
	TeamID = 1;

}

void ACEnemyCharacter::OnDead()
{
	// Widget 설정
	HealthBarWidget->SetVisibility(false);
	// Controller Destroy
	DetachFromControllerPendingDestroy();
	// Capsule 컴포넌트 Collision 설정
	GetCapsuleComponent()->SetCollisionObjectType(ECC_WorldDynamic);
	
	Super::OnDead();
}

void ACEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

}

float ACEnemyCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	UseStatusData.Health -= damage;
	Cast<UCUserWidget_BaseProgressBar>(HealthBarWidget->GetWidget())->UpdateValue(UseStatusData.Health, UseStatusData.MaxHealth);
	
	if(UseStatusData.Health < 0.0f)
	{
		// Dead
		Sound->PlayDeadSound();
		Montage->PlayMontage(EMontageType::Dead);
	}
	else
	{
		// Hit
		Sound->PlayHitSound();
		Montage->PlayMontage(Cast<ACWeapon_Base>(DamageCauser)->GetHitMontageType());
	}
	

	return damage;
}
