#include "Weapon/CWeapon_Near_Hammer.h"
#include "ActionRPGGame.h"
#include "NiagaraFunctionLibrary.h"
#include "Characters/CBaseCharacter.h"

ACWeapon_Near_Hammer::ACWeapon_Near_Hammer()
{
	// WeaponType 초기화
	WeaponType = EWeaponType::Hammer;
	WeaponDamage = 30.0f;
	TraceRadius = 20.0f;

	// 컴포넌트 생성
	HammerStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("WeaponStaticMesh");
	HammerStaticMesh->SetupAttachment(Root);
	
	// StaticMesh'/Game/Weapons/Meshes/SM_Hammer.SM_Hammer'
	const ConstructorHelpers::FObjectFinder<UStaticMesh> staticMeshAsset(TEXT("StaticMesh'/Game/Weapons/Meshes/SM_Hammer.SM_Hammer'"));
	if(staticMeshAsset.Succeeded())
	{
		UStaticMesh* staticMesh = staticMeshAsset.Object;
		HammerStaticMesh->SetStaticMesh(staticMesh);
		HammerStaticMesh->SetCollisionProfileName("NoCollision");
	}

	// Weapon Data Table
	// DataTable'/Game/DataTables/DT_Weapon_Hammer.DT_Weapon_Hammer'
	const ConstructorHelpers::FObjectFinder<UDataTable> weaponDataTableAsset(TEXT("DataTable'/Game/DataTables/DT_Weapon_Hammer.DT_Weapon_Hammer'"));
	if (weaponDataTableAsset.Succeeded())
	{
		WeaponTable = weaponDataTableAsset.Object;
	}

	// Texture2D'/Game/Widgets/Textures/Icon/T_Hammer.T_Hammer'
	const ConstructorHelpers::FObjectFinder<UTexture2D> weaponIconAsset(TEXT("Texture2D'/Game/Widgets/Textures/Icon/T_Hammer.T_Hammer'"));
	if (weaponIconAsset.Succeeded())
	{
		WeaponIcon = weaponIconAsset.Object;
	}
}

void ACWeapon_Near_Hammer::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(IsAttack)
	{
		FVector start = HammerStaticMesh->GetSocketLocation("Start");
		FVector end = HammerStaticMesh->GetSocketLocation("End");
		OnSphereTrace(start, end);
	}
}

void ACWeapon_Near_Hammer::GetStaticMeshComponent(UStaticMeshComponent*& OutStaticMeshComponent)
{
	Super::GetStaticMeshComponent(OutStaticMeshComponent);

	CLog::Log("ACWeapon_Near_Hammer GetStaticMesh");
	OutStaticMeshComponent = HammerStaticMesh;
}
