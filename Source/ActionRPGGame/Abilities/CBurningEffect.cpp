#include "Abilities/CBurningEffect.h"
#include "CGameInstance.h"
#include "NiagaraFunctionLibrary.h"
#include "Characters/CBaseCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetTextLibrary.h"
#include "Widgets/CDamageText.h"
#include "NiagaraComponent.h"
#include "Abilities/CAbility.h"

ACBurningEffect::ACBurningEffect()
{
	PrimaryActorTick.bCanEverTick = true;

	IsTimer = true;
	Damage = 15.0f;

	NiagaraComponent= CreateDefaultSubobject<UNiagaraComponent>("Niagara");
	
	// NiagaraSystem'/Game/Effects/Fire/NiagaraSystems/NS_Burning.NS_Burning'
	const ConstructorHelpers::FObjectFinder<UNiagaraSystem> burningNiagaraSystemAsset(TEXT("NiagaraSystem'/Game/Effects/Fire/NiagaraSystems/NS_Burning.NS_Burning'"));
	if(burningNiagaraSystemAsset.Succeeded())
	{
		BurningEffect = burningNiagaraSystemAsset.Object;
	}

	NiagaraComponent->SetAsset(BurningEffect);
}

void ACBurningEffect::BeginPlay()
{
	Super::BeginPlay();

	SetLifeSpan(12.0f);
}

void ACBurningEffect::BurningDamage()
{
	if(HitCharacter->GetAlive())
	{
		OwnerAbility->SpawnDamageText(HitCharacter->GetMesh()->GetSocketLocation("Burning"), HitCharacter, Damage, true);

		// Take Damage
		FDamageEvent damageEvent;
		HitCharacter->TakeDamage(Damage, damageEvent, GetOwner<ACBaseCharacter>()->GetController(), OwnerAbility);

		IsTimer = true;
	}
}

void ACBurningEffect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsTimer)
	{
		IsTimer = false;
		FTimerHandle waitHandle;
		GetWorld()->GetTimerManager().SetTimer(waitHandle, this, &ACBurningEffect::BurningDamage, 2.0f, false);
	}

	if(!HitCharacter->GetAlive())
	{
		NiagaraComponent->DestroyComponent();
		Destroyed();
	}

}

void ACBurningEffect::InitBurningEffect(ACBaseCharacter* InHitCharacter, ACAbility* InOwnerAbility)
{
	HitCharacter = InHitCharacter;
	OwnerAbility = InOwnerAbility;
}


