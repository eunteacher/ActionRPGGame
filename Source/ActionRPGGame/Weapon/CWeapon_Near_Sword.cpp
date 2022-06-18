#include "Weapon/CWeapon_Near_Sword.h"
#include "ActionRPGGame.h"

// 생성자
ACWeapon_Near_Sword::ACWeapon_Near_Sword()
{
	// WeaponType 초기화
	Weapon = EWeaponType::Sword;

	// 컴포넌트 생성
	WeaponStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	WeaponStaticMesh->SetupAttachment(Root);

	// StaticMesh 초기화
	// StaticMesh'/Game/Weapons/Meshes/SM_sword.SM_sword'
	const ConstructorHelpers::FObjectFinder<UStaticMesh> staticMeshAsset(TEXT("StaticMesh'/Game/Weapons/Meshes/SM_sword.SM_sword'"));
	if(staticMeshAsset.Succeeded())
	{
		UStaticMesh* staticMesh = staticMeshAsset.Object;
		WeaponStaticMesh->SetStaticMesh(staticMesh);
		WeaponStaticMesh->SetCollisionProfileName("NoCollision");
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

// BeginPlay
void ACWeapon_Near_Sword::BeginPlay()
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
			useWeaponData.HitMontageType = data->HitMontageType;
			useWeaponData.HitNiagaraEffect = data->HitNiagaraEffect;
			useWeaponData.ShakeClass = data->ShakeClass;
			UseWeaponDataMaps.Add(data->AttackType, useWeaponData);
		}
	}

}

void ACWeapon_Near_Sword::GetStaticMeshComponent(UStaticMeshComponent*& OutStaticMeshComponent)
{
	CLog::Log("ACWeapon_Near_Sword GetStaticMesh");
	OutStaticMeshComponent = WeaponStaticMesh;
}
