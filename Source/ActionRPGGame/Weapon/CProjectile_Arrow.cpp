#include "Weapon/CProjectile_Arrow.h"
#include "ActionRPGGame.h"
#include "GameFramework/ProjectileMovementComponent.h"

ACProjectile_Arrow::ACProjectile_Arrow()
{
	// StaticMesh 초기화
	// StaticMesh'/Game/Weapons/Meshes/RogueArrow.RogueArrow'
	const ConstructorHelpers::FObjectFinder<UStaticMesh> staticMeshAsset(TEXT("StaticMesh'/Game/Weapons/Meshes/RogueArrow.RogueArrow'"));
	if(staticMeshAsset.Succeeded())
	{
		UStaticMesh* staticMesh = staticMeshAsset.Object;
		StaticMesh->SetStaticMesh(staticMesh);
	}

	// Porjectile 멤버 변수 초기화
	Projectile->InitialSpeed = 5000.0f;
	Projectile->MaxSpeed = 6000.0f;
	Projectile->ProjectileGravityScale = 1.0f;
	Projectile->Velocity = FVector(5000.0f, 0.0f, 0.0f);
}

