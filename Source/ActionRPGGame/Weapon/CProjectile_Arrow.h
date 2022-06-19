#pragma once

#include "CoreMinimal.h"
#include "Weapon/CProjectile.h"
#include "CProjectile_Arrow.generated.h"

UCLASS()
class ACTIONRPGGAME_API ACProjectile_Arrow : public ACProjectile
{
	GENERATED_BODY()
	
public:
	ACProjectile_Arrow();

	virtual void Tick(float DeltaSeconds) override;

	virtual void OnAttach(AActor* InHitActor, FVector InAttachLoaction) override;
	virtual void OnAttach(ACBaseCharacter* InHitCharacter, FName InSocketName) override;
	
protected:
	virtual void BeginPlay() override;
	// StaticMesh 컴포넌트, Projectile의 Mesh
	UPROPERTY(VisibleDefaultsOnly, Category = "Component")
	UStaticMeshComponent* ArrowStaticMesh;

	// ParticleSystem 컴포넌트
	UPROPERTY(VisibleDefaultsOnly,Category = "Component")
	UParticleSystemComponent* ArrowTrail;


};
