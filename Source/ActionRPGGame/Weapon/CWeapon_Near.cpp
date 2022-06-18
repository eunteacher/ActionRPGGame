#include "Weapon/CWeapon_Near.h"
#include "ActionRPGGame.h"
#include "NiagaraFunctionLibrary.h"
#include "Characters/CBaseCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Components/CMontageComponent.h"
#include "Components/CSoundComponent.h"
#include "Kismet/KismetTextLibrary.h"
#include "Types/CDamageType.h"
#include "Widgets/CDamageText.h"

ACWeapon_Near::ACWeapon_Near()
{
	// 멤버 변수 초기화
	CanCombo = false;
	DrawDebugType = EDrawDebugTrace::ForOneFrame;
	TraceType = ETraceTypeQuery::TraceTypeQuery2;
}

void ACWeapon_Near::BeginPlay()
{
	Super::BeginPlay();
	
	
}

void ACWeapon_Near::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(IsAttack)
	{
		OnSphereTrace();
	}
}

void ACWeapon_Near::OnReset()
{
	Super::OnReset();
	CLog::Log("Near OnReset");
	CanCombo = false;
	IsAttack = false;
	AttackType = EAttackType::Near_Combo1;
	HittedActors.Empty();
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

void ACWeapon_Near::OnSphereTrace()
{
	// StaticMesh에 소켓을 추가해야한다.
	FVector start = WeaponStaticMesh->GetSocketLocation("Socket1");
	FVector end = WeaponStaticMesh->GetSocketLocation("Socket2");
	TArray<AActor*> ActorToIgnore;
	ActorToIgnore.Add(GetOwner());
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

				// Spawn DamageText 
				FTransform transform;
				transform.SetLocation(hit.ImpactPoint);
				ACDamageText* damageText = GetWorld()->SpawnActorDeferred<ACDamageText>(DamageTextClass, transform, hitCharacter);
				UGameplayStatics::FinishSpawningActor(damageText, transform);
				bool isPlayer = hitCharacter->GetStatusType() == EStatusType::Player ? true : false;
				damageText->SetDamageText(UKismetTextLibrary::Conv_FloatToText(UseWeaponDataMaps.Find(AttackType)->Damage, ERoundingMode::HalfFromZero), isPlayer);

				// TakeDamage
				FDamageEvent damageEvent(UCDamageType::StaticClass());
				hitCharacter->TakeDamage(UseWeaponDataMaps.Find(AttackType)->Damage, damageEvent, hitCharacter->GetController(), this);
			}
		}
	}
	else
	{
		HittedActors.Empty();
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


