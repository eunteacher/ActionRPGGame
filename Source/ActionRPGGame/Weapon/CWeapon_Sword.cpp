#include "Weapon/CWeapon_Sword.h"
#include "Types/CEnumTypes.h"
#include "Components/CapsuleComponent.h"

ACWeapon_Sword::ACWeapon_Sword()
{
	// 멤버 변수 초기화
	WeaponType = EWeaponType::Sword;
	ComboCount = 1;

	// StaticMesh 컴포넌트 생성
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	StaticMesh->SetupAttachment(Root);
	// StaticMesh'/Game/Weapons/Meshes/SM_sword.SM_sword'
	const ConstructorHelpers::FObjectFinder<UStaticMesh> staticMeshAsset(TEXT("StaticMesh'/Game/Weapons/Meshes/SM_sword.SM_sword'"));
	if(staticMeshAsset.Succeeded())
	{
		UStaticMesh* staticMesh = staticMeshAsset.Object;
		StaticMesh->SetStaticMesh(staticMesh);
	}
	
	// Capsule 컴포넌트 생성
	Capsule = CreateDefaultSubobject<UCapsuleComponent>("Capsule1");
	Capsule->SetupAttachment(StaticMesh);
	Capsule->SetRelativeLocation(FVector(0.0f,0.0f,70.0f));
	Capsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ACWeapon_Sword::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACWeapon_Sword::OnCollision()
{
	Capsule->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void ACWeapon_Sword::OffCollision()
{
	Capsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
