#include "Weapon/CWeapon_Near.h"
#include "ActionRPGGame.h"
#include "NiagaraFunctionLibrary.h"
#include "Characters/CBaseCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Components/CMontageComponent.h"
#include "Components/CSoundComponent.h"
#include "Kismet/KismetTextLibrary.h"

ACWeapon_Near::ACWeapon_Near()
{
	// 멤버 변수 초기화
	CanCombo = false;
	DrawDebugType = EDrawDebugTrace::ForOneFrame;
	TraceType = ETraceTypeQuery::TraceTypeQuery2;
}

void ACWeapon_Near::OnReset()
{
	Super::OnReset();
	CLog::Log("Near OnReset");
	CanCombo = false;
	IsAttack = false;
	AttackType = EAttackType::Near_Combo1;
	HitActors.Empty();
}

void ACWeapon_Near::OnAttack()
{
	CLog::Log("OnAttack");
	
	// 장착되어 있을 경우
	if(IsEquip)
	{
		if(!IsAttack) // IsAttack이 false인 경우
		{
			// 콤보 공격 사용을 위해서 IsAttack을 true로 변경하여 다시 못들어오게 한다.
			IsAttack = true; 
			// 공격 타입을 콤보 공격 1로 설정
			AttackType = EAttackType::Near_Combo1;
		
			UCMontageComponent* montage = Cast<UCMontageComponent>(GetOwner<ACBaseCharacter>()->GetComponentByClass(UCMontageComponent::StaticClass()));
			UCSoundComponent* sound = Cast<UCSoundComponent>(GetOwner<ACBaseCharacter>()->GetComponentByClass(UCSoundComponent::StaticClass()));

			if(UseWeaponDataMaps.Contains(AttackType) && IsValid(montage) && IsValid(sound))
			{
				// AttackType에 맞는 몽타주 실행
				montage->PlayMontage(UseWeaponDataMaps.Find(AttackType)->MontageType);
				// Battle 사운드 실행
				sound->PlayAttackSound();

				LaunchAttacker();
			}			
		}
		else
		{
			// 공격 호출이 들어왓기 때문에 CanCombo를 true
			CanCombo = true;
		}
	}
}

void ACWeapon_Near::ComboAttack()
{
	// CanCombo true인 경우
	if(CanCombo)
	{
		// 다시 못들어오게 하기 위해 CanCombo를 false
		CanCombo = false;

		// Combo1일 경우 Combo2로, Combo2일 경우 Combo3으로
		if (AttackType == EAttackType::Near_Combo1)
		{
			AttackType = EAttackType::Near_Combo2;
		}
		else if(AttackType == EAttackType::Near_Combo2)
		{
			AttackType = EAttackType::Near_Combo3;
		}

		// Character의 Montage와 Sound 컴포넌트를 가져온다.
		UCMontageComponent* montage = Cast<UCMontageComponent>(GetOwner<ACBaseCharacter>()->GetComponentByClass(UCMontageComponent::StaticClass()));
		UCSoundComponent* sound = Cast<UCSoundComponent>(GetOwner<ACBaseCharacter>()->GetComponentByClass(UCSoundComponent::StaticClass()));

		if(UseWeaponDataMaps.Contains(AttackType) && IsValid(montage) && IsValid(sound))
		{
			// AttackType에 맞는 몽타주 실행
			montage->PlayMontage(UseWeaponDataMaps.Find(AttackType)->MontageType);
			// Battle 사운드 실행
			sound->PlayAttackSound();

			LaunchAttacker();
		}
	}
}

void ACWeapon_Near::LaunchAttacker()
{
	FLatentActionInfo info;
	info.CallbackTarget = this;

	const FVector launchLocation = GetOwner<ACBaseCharacter>()->GetActorLocation() + GetOwner<ACBaseCharacter>()->GetActorForwardVector() * UseWeaponDataMaps.Find(AttackType)->LaunchValue;
	const FRotator launchRotation = GetOwner<ACBaseCharacter>()->GetActorRotation();

	// 캐릭터 이동
	UKismetSystemLibrary::MoveComponentTo
	(
		GetOwner<ACBaseCharacter>()->GetCapsuleComponent(),
		launchLocation,
		launchRotation,
		false,
		false,
		0.1f,
		false,
		EMoveComponentAction::Move,
		info
	);
}

void ACWeapon_Near::OnSphereTrace(FVector InStartLocation, FVector InEndLocation)
{
	TArray<AActor*> ActorToIgnore;
	ActorToIgnore.Add(GetOwner());
	FHitResult hit;

	// SphereTrace 시작
	if(UKismetSystemLibrary::SphereTraceSingle(GetWorld(), InStartLocation, InEndLocation, TraceRadius, TraceType, false, ActorToIgnore, DrawDebugType, hit, true))
	{
		// HitActors에 없는 경우, 즉 중복 데미지 방지
		if(!HitActors.Contains(hit.GetActor()))
		{
			HitActors.Add(hit.GetActor());
			ACBaseCharacter* hitCharacter = Cast<ACBaseCharacter>(hit.GetActor());
			if (IsValid(hitCharacter))
			{	
				// Spwan Effect
				if(IsValid(UseWeaponDataMaps.Find(AttackType)->HitNiagaraEffect))
				{
					UNiagaraFunctionLibrary::SpawnSystemAtLocation
					(
						GetWorld(),
						UseWeaponDataMaps.Find(AttackType)->HitNiagaraEffect,
						hit.ImpactPoint,
						hit.ImpactNormal.Rotation()
					);
				}

				float damage = WeaponDamage + WeaponDamage * UseWeaponDataMaps.Find(AttackType)->Damage;

				SpawnDamageText(hit.ImpactPoint, hitCharacter, damage);

				// TakeDamage
				FDamageEvent damageEvent;
				hitCharacter->TakeDamage(damage, damageEvent, hitCharacter->GetController(), this);
			}
		}
	}
	else
	{
		HitActors.Empty();
	}
}



