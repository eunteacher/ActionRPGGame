#pragma once

#include "CoreMinimal.h"
#include "NiagaraSystem.h"
#include "GameFramework/Actor.h"
#include "Kismet/KismetSystemLibrary.h"
#include "CProjectile.generated.h"

// 전방 선언
class UProjectileMovementComponent;
class USphereComponent;

UCLASS()
class ACTIONRPGGAME_API ACProjectile : public AActor
{
	GENERATED_BODY()
	
public:
	// 생성자
	ACProjectile();

	// Tick
	virtual void Tick(float DeltaTime) override;

	void InitHittedInfo(float& InDamage, float& InLaunchValue, UParticleSystem* InHitParticle, UNiagaraSystem* InHitNiagaraEffect);

	UPROPERTY(EditAnywhere, Category = "Trace")
	TEnumAsByte<EDrawDebugTrace::Type> DrawDebugType = EDrawDebugTrace::ForOneFrame;

	UPROPERTY(EditAnywhere, Category = "Trace")
	TEnumAsByte<ETraceTypeQuery> TraceType = ETraceTypeQuery::TraceTypeQuery2;
	
protected:
	// Beginplay
	virtual void BeginPlay() override;

	void OnSphereTrace();
	
	// Scene 컴포넌트, 루트 컴포넌트
	UPROPERTY(VisibleDefaultsOnly, Category = "Component")
	USceneComponent* Root;

	// StaticMesh 컴포넌트, Projectile의 Mesh
	UPROPERTY(VisibleDefaultsOnly, Category = "Component")
	UStaticMeshComponent* StaticMesh;

	// Projectile 컴포넌트
	UPROPERTY(VisibleDefaultsOnly, Category = "Component")
	UProjectileMovementComponent* Projectile;

	// ParticleSystem 컴포넌트
	UPROPERTY(VisibleDefaultsOnly,Category = "Component")
	UParticleSystemComponent* ProjectileTrail;

	// Damage 수치
	UPROPERTY(VisibleDefaultsOnly,Category = "Hit")
	float Damage;

	// 공격 받을 경우, 밀릴 값
	UPROPERTY(VisibleDefaultsOnly,Category = "Hit")
	float LaunchValue;

	// HitParticle
	UPROPERTY(VisibleDefaultsOnly,Category = "Hit")
	UParticleSystem* HitParticle;
	
	UPROPERTY(VisibleDefaultsOnly,Category = "Hit")
	UNiagaraSystem* HitNiagaraEffect;
	
	UPROPERTY(VisibleDefaultsOnly,Category = "LifeTime")
	float LifeTime; // Projectile이 존재하는 시간

	// 이미 공격받은 Actors
	TArray<AActor*> HittedActors;
	
};

