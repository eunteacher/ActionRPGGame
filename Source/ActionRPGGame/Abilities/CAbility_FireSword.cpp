#include "CAbility_FireSword.h"
#include "ActionRPGGame.h"
#include "NiagaraFunctionLibrary.h"
#include "Characters/CBaseCharacter.h"
#include "Characters/CPlayerController.h"
#include "Components/CMontageComponent.h"
#include "Kismet/KismetTextLibrary.h"
#include "Math/TransformCalculus3D.h"
#include "Weapon/CWeapon_Near_Sword.h"
#include "Widgets/CDamageText.h"
#include "CBurningEffect.h"

ACAbility_FireSword::ACAbility_FireSword()
{
	// Type 초기화
	WeaponType = EWeaponType::Sword;
	AbilityType = EAbilityType::FireSword;
	MontageType = EMontageType::FireSword;
	
	// 데미지, 쿨다운, 코스트, 지속시간 초기화
	Damage = 0.2f;
	CoolDown = 10.0f;
	ManaCost = 50.0f;
	Duration = 5;
	AttachSocketName = "EffectSocket";

	// Ability Icon 초기화
	// Texture2D'/Game/Widgets/Textures/Icon/T_FireSwordIcon.T_FireSwordIcon'
	const ConstructorHelpers::FObjectFinder<UTexture2D> abilityIconAsset(TEXT("Texture2D'/Game/Widgets/Textures/Icon/T_FireSwordIcon.T_FireSwordIcon'"));
	if (abilityIconAsset.Succeeded())
	{
		AbilityIcon = abilityIconAsset.Object;
	}

	// Fire Effect 초기화
	// NiagaraSystem'/Game/Effects/Fire/NiagaraSystems/NS_MeshAura.NS_MeshAura'
	const ConstructorHelpers::FObjectFinder<UNiagaraSystem> fireNiagaraSystemAsset(TEXT("NiagaraSystem'/Game/Effects/Fire/NiagaraSystems/NS_MeshAura.NS_MeshAura'"));
	if(fireNiagaraSystemAsset.Succeeded())
	{
		FireEffect = fireNiagaraSystemAsset.Object;
	}

	// Aura Effect 초기화
	// NiagaraSystem'/Game/Effects/Fire/NiagaraSystems/NS_Aura.NS_Aura'
	const ConstructorHelpers::FObjectFinder<UNiagaraSystem> auraNiagaraSystemAsset(TEXT("NiagaraSystem'/Game/Effects/Fire/NiagaraSystems/NS_Aura.NS_Aura'"));
	if(auraNiagaraSystemAsset.Succeeded())
	{
		AuraEffect = auraNiagaraSystemAsset.Object;
	}

	// Blueprint'/Game/Abilities/BP_CBurningEffect.BP_CBurningEffect'
	ConstructorHelpers::FClassFinder<ACBurningEffect> burningEffectBlueprintClass(TEXT("Blueprint'/Game/Abilities/BP_CBurningEffect.BP_CBurningEffect_C'"));
	if(burningEffectBlueprintClass.Succeeded())
	{
		BurningEffectClass = burningEffectBlueprintClass.Class;
	}

}

void ACAbility_FireSword::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(IsActivation)
	{
		OnSphereTrace();
	}
}

void ACAbility_FireSword::OnActivation()
{
	Super::OnActivation();
	
	CLog::Print(FString("FireSword OnActivation"));

	if(IsAvailable)
	{
		IsAvailable = false;
		IsActivation = true;

		// Ability Slot 쿨다운 호출 
		ACPlayerController* playerController = OwnerCharacter->GetController<ACPlayerController>();
		if(playerController->OnAbilityActivated.IsBound())
		{
			playerController->OnAbilityActivated.Broadcast(this);
		}

		UCMontageComponent* montage = Cast<UCMontageComponent>(OwnerCharacter->GetComponentByClass(UCMontageComponent::StaticClass()));
		if(IsValid(montage))
		{
			montage->PlayMontage(MontageType);
		}

		if(IsValid(AuraEffect))
		{
			FVector location = OwnerCharacter->GetActorLocation();
			location.Z -= 90.0f;
		
			UNiagaraFunctionLibrary::SpawnSystemAtLocation
			(
				GetWorld(),
				AuraEffect,
				location,
				OwnerCharacter->GetActorRotation()
			);
		} // IsValid AuraEffect
	} // IsAvailable
}

void ACAbility_FireSword::OnProgress()
{
	Super::OnProgress();

	if(IsValid(FireEffect))
	{
		UStaticMeshComponent* staticMeshComponent = nullptr;
		OwnerWeapon->GetStaticMeshComponent(staticMeshComponent);
		UNiagaraFunctionLibrary::SpawnSystemAttached
		(
			FireEffect,
			staticMeshComponent,
			AttachSocketName,
			FVector::ZeroVector,
			FRotator::ZeroRotator,
			EAttachLocation::KeepRelativeOffset,
			true
		);	
	}

	OriginalDamage = OwnerWeapon->GetWeaponDamage();
	OwnerWeapon->SetWeaponDamage(OriginalDamage + OriginalDamage * Damage);
}

void ACAbility_FireSword::OnDeActivation()
{
	Super::OnDeActivation();
	CLog::Print(FString("SwordFire OnDeActivation"));

	IsActivation = false;

	OwnerWeapon->SetWeaponDamage(OriginalDamage);
	HittedActors.Empty();
}

void ACAbility_FireSword::OnSphereTrace()
{
	// StaticMesh에 소켓을 추가해야한다.
	UStaticMeshComponent* staticMeshComponent = nullptr;
	OwnerWeapon->GetStaticMeshComponent(staticMeshComponent);
	FVector start = staticMeshComponent->GetSocketLocation("Socket1");
	FVector end = staticMeshComponent->GetSocketLocation("Socket2");
	TArray<AActor*> ActorToIgnore;
	ActorToIgnore.Add(OwnerCharacter);
	FHitResult hit;

	// SphereTrace 시작
	if(UKismetSystemLibrary::SphereTraceSingle(GetWorld(), start, end, 5.0f, TraceType, false, ActorToIgnore, DrawDebugType, hit, true))
	{
		// HittedActors에 없는 경우, 즉 중복 데미지 방지
		if(!HittedActors.Contains(hit.GetActor()))
		{
			HittedActors.Add(hit.GetActor());
			ACBaseCharacter* hitCharacter = Cast<ACBaseCharacter>(hit.GetActor());
			if (IsValid(hitCharacter))
			{
				if(IsValid(BurningEffectClass))
				{
					FTransform transform;
					ACBurningEffect* burningEffect = GetWorld()->SpawnActorDeferred<ACBurningEffect>(BurningEffectClass, transform, OwnerCharacter);
					burningEffect->InitBurningEffect(hitCharacter, this);
					burningEffect->AttachToActor(hitCharacter,FAttachmentTransformRules(EAttachmentRule::KeepRelative, true),"Burning");
					UGameplayStatics::FinishSpawningActor(burningEffect, transform);
				} // if IsValid BuringEffectClass
			} // If IsValid hitCharacter
		}
	}
}
