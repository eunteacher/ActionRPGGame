#include "Weapon/CWeapon_Base.h"
#include "ActionRPGGame.h"
#include "Charactets/CBaseCharacter.h"
#include "Components/CMontageComponent.h"
#include "Components/CSoundComponent.h"
#include "Types/CEnumTypes.h"

ACWeapon_Base::ACWeapon_Base()
{
	// PrimaryActorTick.bCanEverTick = true;

	// 루트 컴포넌트 생성
	Root = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(Root);

	// 멤버 변수 초기화
	IsEquip = false;

	// Weapon Data Table
	// DataTable'/Game/DataTables/DT_Wepaon.DT_Wepaon'
	static ConstructorHelpers::FObjectFinder<UDataTable> WeaponDataTableAsset(TEXT("DataTable'/Game/DataTables/DT_Wepaon.DT_Wepaon'"));
	if (WeaponDataTableAsset.Succeeded())
	{
		WeaponTable = WeaponDataTableAsset.Object;
	}
}

void ACWeapon_Base::BeginPlay()
{
	Super::BeginPlay();

	if(IsValid(WeaponTable))
	{
		// 데이터 테이블의 데이터를 읽어와서 저장
		WeaponTable->GetAllRows<FWeaponData>("", WeaponData);
	}
}

// 무기 장착 몽타주 실행 
void ACWeapon_Base::OnEquip()
{
	if(IsValid(GetOwner<ACBaseCharacter>()))
	{
		UCMontageComponent* montage = Cast<UCMontageComponent>(GetOwner<ACBaseCharacter>()->GetComponentByClass(UCMontageComponent::StaticClass()));
		UCSoundComponent* sound = Cast<UCSoundComponent>(GetOwner<ACBaseCharacter>()->GetComponentByClass(UCSoundComponent::StaticClass()));
		// 무기가 장착되어 있지 않고, WeaponType이 캐릭터의 WeaponType과 같을 경우
		if (!IsEquip && GetOwner<ACBaseCharacter>()->GetWeaponType() == Weapon) 
		{
			IsEquip = true; // 무기 장착 여부 true
			
			// 무기를 소유한 캐릭터의 Montage 컴포넌트를 가져온다.
			if (IsValid(montage) && IsValid(sound))
			{
				// WeaponType에 맞게 몽타주 실행
				if (Weapon == EWeaponType::Sword)
				{
					montage->PlayMontage(GetOwner<ACBaseCharacter>()->GetModelType(), EMontageType::Equip_Sword);
				}
				else if (Weapon == EWeaponType::Bow)
				{
					montage->PlayMontage(GetOwner<ACBaseCharacter>()->GetModelType(), EMontageType::Equip_Bow);
				}
				// 사운드 플레이
				sound->PlayEquipSound();
			} // montage && state
		} // bEquip && GetWeapon == Weapon
	} // GetOwner
}

// 무기 해제
void ACWeapon_Base::OnUnEquip()
{
	if(IsValid(GetOwner<ACBaseCharacter>()))
	{
		UCMontageComponent* montage = Cast<UCMontageComponent>(GetOwner<ACBaseCharacter>()->GetComponentByClass(UCMontageComponent::StaticClass()));
		UCSoundComponent* sound = Cast<UCSoundComponent>(GetOwner<ACBaseCharacter>()->GetComponentByClass(UCSoundComponent::StaticClass()));
		// 무기가 장착되어 있고, WeaponType이 캐릭터의 WeaponType과 같을 경우
		if (IsEquip && GetOwner<ACBaseCharacter>()->GetWeaponType() == Weapon)
		{
			IsEquip = false; // 무기 장착 여부 false
			// 무기를 소유한 캐릭터의 Montage 컴포넌트를 가져온다.
			if (IsValid(montage) && IsValid(sound))
			{
				// WeaponType에 맞게 몽타주 실행
				if (Weapon == EWeaponType::Sword)
				{
					montage->PlayMontage(GetOwner<ACBaseCharacter>()->GetModelType(), EMontageType::UnEquip_Sword);
				}
				else if (Weapon == EWeaponType::Bow)
				{
					montage->PlayMontage(GetOwner<ACBaseCharacter>()->GetModelType(), EMontageType::UnEquip_Sword);
				}
				// 사운드 플레이
				sound->PlayEquipSound();
			} // montage
		} // bEquip && GetWeapon == Weapon		
	} // GetOwner

}

// 무기를 캐릭터의 Mesh의 입력받은 소켓에 Attach한다.
void ACWeapon_Base::OnAttach(FName InSocketName)
{
	AttachToComponent(GetOwner<ACBaseCharacter>()->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), InSocketName);
}

void ACWeapon_Base::OnCollision()
{
	// 자식 클래스에서 정의
}

void ACWeapon_Base::OffCollision()
{
	// 자식 클래스에서 정의
}

void ACWeapon_Base::OnAttack()
{
	// 자식 클래스에서 정의
}

void ACWeapon_Base::OnReset()
{
	// 자식 클래스에서 정의
}



