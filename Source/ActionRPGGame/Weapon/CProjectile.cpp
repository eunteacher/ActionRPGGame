#include "Weapon/CProjectile.h"
#include "ActionRPGGame.h"
#include "Charactets/CBaseCharacter.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/CMontageComponent.h"
#include "Kismet/KismetTextLibrary.h"
#include "Types/CDamageType.h"
#include "Types/CEnumTypes.h"
#include "Widgets/CDamageText.h"

ACProjectile::ACProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	// 멤버 변수 초기화
	DrawDebugType = EDrawDebugTrace::None;
	TraceType = ETraceTypeQuery::TraceTypeQuery2;
	LifeTime = 5.0f;
	IsAttach = false;
	
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

// Projectile의 필요한 Htited 데이터 초기화 함수
void ACProjectile::InitHittedInfo(float& InDamage, float& InLaunchValue, UNiagaraSystem* InHitNiagaraEffect, TSubclassOf<ACDamageText>& InDamageTextClass, bool InIsAttach)
{
	Damage = InDamage;
	LaunchValue = InLaunchValue;
	HitNiagaraEffect = InHitNiagaraEffect;
	DamageTextClass = InDamageTextClass;
	IsAttach = InIsAttach;
}

// Sphere Trace
// Spawn Effect, HeadShot 유무, Hit된 Character Laucnch, TakeDamage, Attach
void ACProjectile::OnSphereTrace()
{
	// StaticMesh에 소켓을 추가해야한다.
	FVector start = StaticMesh->GetSocketLocation("Socket1");
	FVector end = StaticMesh->GetSocketLocation("Socket2");
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
			FName closedBone = hit.BoneName;
			if (IsValid(hitCharacter))
			{
				// 타격된 부위가 Head일 경우, 원래 Damage의 2배에 해당하는 Damage를 입힌다.
				if(closedBone.ToString().Contains("Head"))
				{
					CLog::Print(FString("HeadShot"));
					Damage *= 2.0f;
				}
				else
				{
					if(closedBone == "None")
					{
						// 가장 가까운 Bone 찾기
						TArray<FName> BoneNames = hitCharacter->GetMesh()->GetAllSocketNames();
						float min = UKismetMathLibrary::Vector_Distance(hit.ImpactPoint, hitCharacter->GetMesh()->GetSocketLocation("root"));
						for(FName boneName : BoneNames)
						{
							FVector boneLocation = hitCharacter->GetMesh()->GetSocketLocation(boneName);
							float distance = UKismetMathLibrary::Vector_Distance(hit.ImpactPoint, boneLocation);
							if(min > distance)
							{
								min = distance;
								closedBone = boneName;
							}
						}
					}
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

				// Spawn DamageText 
				FTransform transform;
				transform.SetLocation(hit.ImpactPoint);
				ACDamageText* damageText = GetWorld()->SpawnActorDeferred<ACDamageText>(DamageTextClass, transform, hitCharacter);
				UGameplayStatics::FinishSpawningActor(damageText, transform);
				bool isPlayer = hitCharacter->GetStatusType() == EStatusType::Player ? true : false;
				damageText->SetDamageText(UKismetTextLibrary::Conv_FloatToText(Damage, ERoundingMode::HalfFromZero), isPlayer);

				// TakeDamage
				FDamageEvent damageEvent(UCDamageType::StaticClass());
				hitCharacter->TakeDamage(Damage, damageEvent, hitCharacter->GetController(), GetOwner());

				// Attach
				OnAttach(hitCharacter, closedBone);

			}
			else
			{
				CLog::Log(FString("Not BaseCharacter"));
				// Attach
				OnAttach(hit.GetActor(), hit.ImpactPoint);
			}
		}
	}
}

void ACProjectile::OnAttach(ACBaseCharacter* InHitCharacter, FName InSocketName)
{
	if(IsAttach)
	{
		// Projectile 컴포넌트를 삭제한다.
		Projectile->DestroyComponent();
		// HitCharacter에 Projectile을 Attach 한다.
		AttachToComponent(InHitCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepWorld, true), InSocketName);
		// 위치 조정
		SetActorLocation(InHitCharacter->GetMesh()->GetSocketLocation(InSocketName) + GetActorForwardVector() * -75.0f, false, nullptr, ETeleportType::TeleportPhysics);
		// 트레일 종료
		ProjectileTrail->EndTrails();		
	}
	else
	{
		Destroy();
	}
}

void ACProjectile::OnAttach(AActor* InHitActor, FVector InAttachLoaction)
{
	if(IsAttach)
	{
		// Projectile 컴포넌트를 삭제한다.
		Projectile->DestroyComponent();
		// HitActor에 Proejctile을 Attach한다.
		AttachToActor(InHitActor,FAttachmentTransformRules(EAttachmentRule::KeepWorld, true));
		// HitImpact 위치로 위치를 조정한다.
		SetActorLocation(InAttachLoaction + GetActorForwardVector() * -40.0f, false, nullptr, ETeleportType::TeleportPhysics);
		// 트레일 종료
		ProjectileTrail->EndTrails();		
	}
	else
	{
		Destroy();
	}
}

