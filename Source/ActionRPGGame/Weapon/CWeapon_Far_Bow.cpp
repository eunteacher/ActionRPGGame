#include "Weapon/CWeapon_Far_Bow.h"
#include "ActionRPGGame.h"
#include "CAnimInstance_Bow.h"
#include "Camera/CameraComponent.h"
#include "Charactets/CBaseCharacter.h"
#include "Weapon/CProjectile.h"
ACWeapon_Far_Bow::ACWeapon_Far_Bow()
{
	PrimaryActorTick.bCanEverTick = true;
	
	// WeaponType 초기화
	Weapon = EWeaponType::Bow;

	// SkeletalMesh 초기화
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMesh");
	SkeletalMesh->SetupAttachment(Root);
	// SkeletalMesh'/Game/Weapons/Meshes/SK_ElvenBow.SK_ElvenBow'
	const ConstructorHelpers::FObjectFinder<USkeletalMesh> skeletalMeshAsset(TEXT("SkeletalMesh'/Game/Weapons/Meshes/SK_ElvenBow.SK_ElvenBow'"));
	if(skeletalMeshAsset.Succeeded())
	{
		USkeletalMesh* skeletalMesh = skeletalMeshAsset.Object;
		SkeletalMesh->SetSkeletalMesh(skeletalMesh);
	}

	// AnimInstance 생성 및 초기화
	// AnimBlueprint'/Game/Weapons/Animations/ABP_Bow.ABP_Bow'
	ConstructorHelpers::FClassFinder<UAnimInstance> animInstanceClass(TEXT("AnimBlueprint'/Game/Weapons/Animations/ABP_Bow.ABP_Bow_C'"));
	if (animInstanceClass.Succeeded())
	{
		const TSubclassOf<UAnimInstance> animInstance = animInstanceClass.Class;
		SkeletalMesh->SetAnimInstanceClass(animInstance);
	}
	
	// StaticMesh 초기화
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	StaticMesh->SetupAttachment(SkeletalMesh, "Arrow");
	// StaticMesh'/Game/Weapons/Meshes/RogueArrow.RogueArrow'
	const ConstructorHelpers::FObjectFinder<UStaticMesh> staticMeshAsset(TEXT("StaticMesh'/Game/Weapons/Meshes/RogueArrow.RogueArrow'"));
	if(staticMeshAsset.Succeeded())
	{
		UStaticMesh* staticMesh = staticMeshAsset.Object;
		StaticMesh->SetStaticMesh(staticMesh);
		StaticMesh->SetCollisionProfileName("NoCollision");
		StaticMesh->SetVisibility(false);
	}

	// Weapon Data Table
	// DataTable'/Game/DataTables/DT_Weapon_Bow.DT_Weapon_Bow'
	const ConstructorHelpers::FObjectFinder<UDataTable> WeaponDataTableAsset(TEXT("DataTable'/Game/DataTables/DT_Weapon_Bow.DT_Weapon_Bow'"));
	if (WeaponDataTableAsset.Succeeded())
	{
		WeaponTable = WeaponDataTableAsset.Object;
	}
	
	// Projectile Blueprint 클래스를 가져와서 저장
	// Blueprint'/Game/Weapons/Blueprints/BP_CProjectile_Arrow.BP_CProjectile_Arrow'
	ConstructorHelpers::FClassFinder<ACProjectile> ProjectileBlueprintClass(TEXT("Blueprint'/Game/Weapons/Blueprints/BP_CProjectile_Arrow.BP_CProjectile_Arrow_C'"));
	if(ProjectileBlueprintClass.Succeeded())
	{
		ProjectileClass = ProjectileBlueprintClass.Class;
	}
}

// BeginPlay
void ACWeapon_Far_Bow::BeginPlay()
{
	Super::BeginPlay();
	
	if(IsValid(WeaponTable))
	{
		// 데이터 테이블의 데이터를 읽어와서 저장
		TArray<FWeaponData*> weaponDatas;
		WeaponTable->GetAllRows<FWeaponData>("", weaponDatas);
		for (FWeaponData* data : weaponDatas)
		{
			FUseWeaponData useWeaponData;
			useWeaponData.MontageType = data->MontageType;
			useWeaponData.Damage = data->Damage;
			useWeaponData.LaunchValue = data->LaunchValue;
			useWeaponData.HitStopTime = data->HitStopTime;
			useWeaponData.HitParticle = data->HitParticle;
			useWeaponData.HitNiagaraEffect = data->HitNiagaraEffect;
			useWeaponData.ShakeClass = data->ShakeClass;
			UseWeaponDataMaps.Add(data->AttackType, useWeaponData);
		}
	}

	UCAnimInstance_Bow* animInstance_Bow = Cast<UCAnimInstance_Bow>(SkeletalMesh->GetAnimInstance());
	if (IsValid(animInstance_Bow))
	{
		CLog::Log("IsValid(animInstance_Bow)");
		ACBaseCharacter* ownerCharacter = GetOwner<ACBaseCharacter>();
		animInstance_Bow->InitAnimInstance(ownerCharacter);
	}
}
// Tick
void ACWeapon_Far_Bow::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (IsOverDraw)
	{
		StaticMesh->SetVisibility(true);
	}
	else
	{
		StaticMesh->SetVisibility(false);
	}
}

// Projectile 액터 스폰과 값을 정의해준다.
void ACWeapon_Far_Bow::OnFire()
{
	Super::OnFire();

	if(IsValid(ProjectileClass))
	{
		// 스폰될 Projectile의 Transform 정의
		FTransform transform;
		FVector location = OwnerCamera->GetComponentLocation() + OwnerCamera->GetForwardVector() * 100.0f;
		transform.SetLocation(location);
		FRotator rotation = GetOwner<ACBaseCharacter>()->GetControlRotation();
		transform.SetRotation(rotation.Quaternion());

		ACProjectile* projectile = GetWorld()->SpawnActorDeferred<ACProjectile>(ProjectileClass, transform, GetOwner<ACBaseCharacter>());
		projectile->InitHittedInfo
		(
			UseWeaponDataMaps.Find(AttackType)->Damage,
			UseWeaponDataMaps.Find(AttackType)->LaunchValue,
			UseWeaponDataMaps.Find(AttackType)->HitParticle,
			UseWeaponDataMaps.Find(AttackType)->HitNiagaraEffect
		);
		UGameplayStatics::FinishSpawningActor(projectile, transform);
	}
}

