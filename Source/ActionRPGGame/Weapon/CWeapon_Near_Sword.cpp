#include "Weapon/CWeapon_Near_Sword.h"
#include "ActionRPGGame.h"
#include "NiagaraFunctionLibrary.h"
#include "Characters/CBaseCharacter.h"

// 생성자
ACWeapon_Near_Sword::ACWeapon_Near_Sword()
{
	// WeaponType 초기화
	WeaponType = EWeaponType::Sword;
	WeaponDamage = 30.0f;
	TraceRadius = 10.0f;

	// 컴포넌트 생성
	SwordStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("WeaponStaticMesh");
	SwordStaticMesh->SetupAttachment(Root);

	// StaticMesh 초기화
	// StaticMesh'/Game/Weapons/Meshes/SM_sword.SM_sword'
	const ConstructorHelpers::FObjectFinder<UStaticMesh> staticMeshAsset(TEXT("StaticMesh'/Game/Weapons/Meshes/SM_sword.SM_sword'"));
	if(staticMeshAsset.Succeeded())
	{
		UStaticMesh* staticMesh = staticMeshAsset.Object;
		SwordStaticMesh->SetStaticMesh(staticMesh);
		SwordStaticMesh->SetCollisionProfileName("NoCollision");
	}
	
	// Weapon Data Table
	// DataTable'/Game/DataTables/DT_Wepaon_Sword.DT_Wepaon_Sword'
	const ConstructorHelpers::FObjectFinder<UDataTable> weaponDataTableAsset(TEXT("DataTable'/Game/DataTables/DT_Wepaon_Sword.DT_Wepaon_Sword'"));
	if (weaponDataTableAsset.Succeeded())
	{
		WeaponTable = weaponDataTableAsset.Object;
	}

	// Texture2D'/Game/Widgets/Textures/Icon/T_Sword.T_Sword'
	const ConstructorHelpers::FObjectFinder<UTexture2D> weaponIconAsset(TEXT("Texture2D'/Game/Widgets/Textures/Icon/T_Sword.T_Sword'"));
	if (weaponIconAsset.Succeeded())
	{
		WeaponIcon = weaponIconAsset.Object;
	}

}

void ACWeapon_Near_Sword::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(IsAttack)
	{
		FVector start = SwordStaticMesh->GetSocketLocation("Start");
		FVector end = SwordStaticMesh->GetSocketLocation("End");
		OnSphereTrace(start, end);
	}
}

void ACWeapon_Near_Sword::GetStaticMeshComponent(UStaticMeshComponent*& OutStaticMeshComponent)
{
	Super::GetStaticMeshComponent(OutStaticMeshComponent);

	CLog::Log("ACWeapon_Near_Sword GetStaticMesh");
	OutStaticMeshComponent = SwordStaticMesh;
}


