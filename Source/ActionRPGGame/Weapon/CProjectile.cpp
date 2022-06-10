#include "Weapon/CProjectile.h"
#include "ActionRPGGame.h"
#include "Charactets/CBaseCharacter.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "NiagaraFunctionLibrary.h"

ACProjectile::ACProjectile()
{
	PrimaryActorTick.bCanEverTick = true;
	DrawDebugType = EDrawDebugTrace::None;
	TraceType = ETraceTypeQuery::TraceTypeQuery2;
	LifeTime = 5.0f;
	
	// 컴포넌트 생성 및 초기화
	Root = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(Root);
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	StaticMesh->SetupAttachment(Root);
	StaticMesh->SetCollisionProfileName("NoCollision");
	Projectile = CreateDefaultSubobject<UProjectileMovementComponent>("Projectile");

	// ParticleSystemComponent 생성 및 초기화
	ProjectileTrail = CreateDefaultSubobject<UParticleSystemComponent>("ArrowTrail");
	ProjectileTrail->SetupAttachment(StaticMesh);

	// ParticleSystem'/Game/Effects/Trails/ParticleSystems/PS_ProjectileTrail.PS_ProjectileTrail'
	const ConstructorHelpers::FObjectFinder<UParticleSystem> projectileTrailParticleSystemAsset(TEXT("ParticleSystem'/Game/Effects/Trails/ParticleSystems/PS_ProjectileTrail.PS_ProjectileTrail'"));
	if(projectileTrailParticleSystemAsset.Succeeded())
	{
		ProjectileTrail->SetTemplate(projectileTrailParticleSystemAsset.Object);
	}
}

void ACProjectile::BeginPlay()
{
	Super::BeginPlay();
	ProjectileTrail->BeginTrails("Socket1", "Socket2", ETrailWidthMode_FromFirst, 3.0f);
	SetLifeSpan(LifeTime);
}

void ACProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	OnSphereTrace();
}

void ACProjectile::OnSphereTrace()
{
	// StaticMesh에 소켓을 추가해야한다.
	FVector start = StaticMesh->GetSocketLocation("Socket1");
	FVector end = StaticMesh->GetSocketLocation("Socket2");
	TArray<AActor*> ActorToIgnore;
	ActorToIgnore.Add(GetOwner());
	FHitResult hit;

	// SphereTrace 시작
	if(UKismetSystemLibrary::SphereTraceSingle(GetWorld(), start, end, 8.0f, TraceType, false, ActorToIgnore, DrawDebugType, hit, true))
	{
		// HittedActors에 없는 경우, 즉 중복 데미지 방지
		if(!HittedActors.Contains(hit.GetActor()))
		{
			HittedActors.Add(hit.GetActor());
			ACBaseCharacter* hitCharacter = Cast<ACBaseCharacter>(hit.GetActor());
			if (IsValid(hitCharacter))
			{
				// 타격된 부위가 Head일 경우, 원래 Damage의 2배에 해당하는 Damage를 입힌다.
				if(hit.BoneName.ToString().Contains("Head"))
				{
					CLog::Print(FString("HeadShot"));
					Damage *= 2.0f;
				}

				// Effect 스폰
				if(IsValid(HitNiagaraEffect))
				{
					UNiagaraFunctionLibrary::SpawnSystemAtLocation
					(
						GetWorld(),
						HitNiagaraEffect,
						hit.ImpactPoint,
						hit.ImpactNormal.Rotation()
					);
				}

				// 타격시 Launch 
				FVector direction = hitCharacter->GetActorForwardVector() * -1.0f * LaunchValue;
				hitCharacter->LaunchCharacter(direction, false, false);

				// TODO : Damage Event 직접 만들기 
				FDamageEvent e;
				hitCharacter->TakeDamage(Damage, e, hitCharacter->GetController(), this);

			}
		}
	}
}


void ACProjectile::InitHittedInfo(float& InDamage, float& InLaunchValue, UParticleSystem* InHitParticle, UNiagaraSystem* InHitNiagaraEffect)
{
	Damage = InDamage;
	LaunchValue = InLaunchValue;
	HitParticle = InHitParticle;
	HitNiagaraEffect = InHitNiagaraEffect;
}

