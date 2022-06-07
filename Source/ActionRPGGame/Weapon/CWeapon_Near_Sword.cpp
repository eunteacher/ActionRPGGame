#include "Weapon/CWeapon_Near_Sword.h"
#include "ActionRPGGame.h"
#include "Components/CapsuleComponent.h"

// 생성자
ACWeapon_Near_Sword::ACWeapon_Near_Sword()
{
	// WeaponType 초기화
	Weapon = EWeaponType::Sword;

	// StaticMesh 컴포넌트 초기화
	// StaticMesh'/Game/Weapons/Meshes/SM_sword.SM_sword'
	const ConstructorHelpers::FObjectFinder<UStaticMesh> staticMeshAsset(TEXT("StaticMesh'/Game/Weapons/Meshes/SM_sword.SM_sword'"));
	if(staticMeshAsset.Succeeded())
	{
		UStaticMesh* staticMesh = staticMeshAsset.Object;
		StaticMesh->SetStaticMesh(staticMesh);
		StaticMesh->SetCollisionProfileName("NoCollision");
	}
	
	// Capsule 컴포넌트 초기화
	Capsule->SetRelativeLocation(FVector(0.0f,0.0f,60.0f));
	Capsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// Weapon Data Table
	// DataTable'/Game/DataTables/DT_Wepaon_Sword.DT_Wepaon_Sword'
	const ConstructorHelpers::FObjectFinder<UDataTable> WeaponDataTableAsset(TEXT("DataTable'/Game/DataTables/DT_Wepaon_Sword.DT_Wepaon_Sword'"));
	if (WeaponDataTableAsset.Succeeded())
	{
		WeaponTable = WeaponDataTableAsset.Object;
	}
}
// BeginPlay
void ACWeapon_Near_Sword::BeginPlay()
{
	Super::BeginPlay();

	if(IsValid(WeaponTable))
	{
		// 데이터 테이블의 데이터를 읽어와서 저장
		WeaponTable->GetAllRows<FWeaponData>("", WeaponData);
	}
}
