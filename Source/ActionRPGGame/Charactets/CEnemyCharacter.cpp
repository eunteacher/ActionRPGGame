#include "Charactets/CEnemyCharacter.h"
#include "ActionRPGGame.h"

ACEnemyCharacter::ACEnemyCharacter()
{
	// TeamID 초기화
	TeamID = 1;

	

}

void ACEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

}

float ACEnemyCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	

	return damage;
}
