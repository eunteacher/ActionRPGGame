#pragma once

#include "CoreMinimal.h"
#include "NiagaraSystem.h"
#include "GameFramework/Actor.h"
#include "Kismet/KismetSystemLibrary.h"
#include "CProjectile.generated.h"

// 전방 선언
class UProjectileMovementComponent;
class USphereComponent;
class ACDamageText;
enum class EMontageType : uint8;

UCLASS()
class ACTIONRPGGAME_API ACProjectile : public AActor
{
	GENERATED_BODY()
	
public:
	// 생성자
	ACProjectile();

	// Tick
	virtual void Tick(float DeltaTime) override;

	// Projectile Hit 정보 초기화 
	void InitHitInfo(float& InDamage, float& InLaunchValue, UNiagaraSystem* InHitNiagaraEffect, TSubclassOf<ACDamageText>& InDamageTextClass, bool InIsAttach = false);

	UPROPERTY(EditAnywhere, Category = "Trace")
	TEnumAsByte<EDrawDebugTrace::Type> DrawDebugType;

	UPROPERTY(EditAnywhere, Category = "Trace")
	TEnumAsByte<ETraceTypeQuery> TraceType;
protected:
	// Beginplay
	virtual void BeginPlay() override;

	void OnSphereTrace();
	void OnAttach(class ACBaseCharacter* InHitCharacter, FName InSocketName);
	void OnAttach(AActor* InHitActor, FVector InAttachLoaction);
	
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

	UPROPERTY(VisibleDefaultsOnly,Category = "LifeTime")
	float LifeTime; // Projectile이 존재하는 시간

	// HitEvent가 발생했을 경우, Attach 여부
	UPROPERTY(VisibleDefaultsOnly,Category = "Hit")
	bool IsAttach;

	// Damage 수치
	UPROPERTY(VisibleDefaultsOnly,Category = "Hit")
	float Damage;

	// 공격 받을 경우, 밀릴 값
	UPROPERTY(VisibleDefaultsOnly,Category = "Hit")
	float LaunchValue;

	// HitParticle
	UPROPERTY(VisibleDefaultsOnly,Category = "Hit")
	EMontageType HitMontageType;
	
	UPROPERTY(VisibleDefaultsOnly,Category = "Hit")
	UNiagaraSystem* HitNiagaraEffect;

	UPROPERTY(VisibleDefaultsOnly,Category = "Hit")
	TSubclassOf<ACDamageText> DamageTextClass;

	// 이미 공격받은 Actors
	TArray<AActor*> HittedActors;
};

