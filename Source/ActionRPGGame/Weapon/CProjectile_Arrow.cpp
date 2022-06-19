#include "Weapon/CProjectile_Arrow.h"
#include "ActionRPGGame.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"

ACProjectile_Arrow::ACProjectile_Arrow()
{
	// StaticMesh 초기화
	ArrowStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("ArrowStaticMesh");
	ArrowStaticMesh->SetupAttachment(Root);
	ArrowStaticMesh->SetCollisionProfileName("NoCollision");
	
	// StaticMesh'/Game/Weapons/Meshes/RogueArrow.RogueArrow'
	const ConstructorHelpers::FObjectFinder<UStaticMesh> staticMeshAsset(TEXT("StaticMesh'/Game/Weapons/Meshes/RogueArrow.RogueArrow'"));
	if(staticMeshAsset.Succeeded())
	{
		UStaticMesh* staticMesh = staticMeshAsset.Object;
		ArrowStaticMesh->SetStaticMesh(staticMesh);
	}

	// ParticleSystemComponent 생성 및 초기화
	ArrowTrail = CreateDefaultSubobject<UParticleSystemComponent>("ArrowTrail");
	ArrowTrail->SetupAttachment(ArrowStaticMesh);

	// ParticleSystem'/Game/Effects/Trails/ParticleSystems/PS_ProjectileTrail.PS_ProjectileTrail'
	const ConstructorHelpers::FObjectFinder<UParticleSystem> projectileTrailParticleSystemAsset(TEXT("ParticleSystem'/Game/Effects/Trails/ParticleSystems/PS_ProjectileTrail.PS_ProjectileTrail'"));
	if(projectileTrailParticleSystemAsset.Succeeded())
	{
		ArrowTrail->SetTemplate(projectileTrailParticleSystemAsset.Object);
	}

	// Porjectile 멤버 변수 초기화
	Projectile->InitialSpeed = 5000.0f;
	Projectile->MaxSpeed = 6000.0f;
	Projectile->ProjectileGravityScale = 1.0f;
	Projectile->Velocity = FVector(5000.0f, 0.0f, 0.0f);
}

void ACProjectile_Arrow::BeginPlay()
{
	Super::BeginPlay();
	ArrowTrail->BeginTrails("Start", "End", ETrailWidthMode_FromFirst, 3.0f);
}

void ACProjectile_Arrow::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	FVector start = ArrowStaticMesh->GetSocketLocation("Start");
	FVector end = ArrowStaticMesh->GetSocketLocation("End");
	OnSphereTrace(start, end);
}

void ACProjectile_Arrow::OnAttach(AActor* InHitActor, FVector InAttachLoaction)
{
	Super::OnAttach(InHitActor, InAttachLoaction);
	ArrowTrail->EndTrails();		
}

void ACProjectile_Arrow::OnAttach(ACBaseCharacter* InHitCharacter, FName InSocketName)
{
	Super::OnAttach(InHitCharacter, InSocketName);
	ArrowTrail->EndTrails();		
}

