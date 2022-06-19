#include "Weapon/CWeapon.h"
#include "ActionRPGGame.h"
#include "CGameInstance.h"
#include "Characters/CBaseCharacter.h"
#include "Components/CMontageComponent.h"
#include "Types/CEnumTypes.h"

ACWeapon::ACWeapon()
{
	PrimaryActorTick.bCanEverTick = true;

	// 멤버 변수 초기화
	IsEquip = false;
	IsAttack = false;
	
	// 컴포넌트 생성 및 초기화
	Root = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(Root);
}

void ACWeapon::GetStaticMeshComponent(UStaticMeshComponent*& OutStaticMeshComponent)
{
	CLog::Log("ACWeapon_Base GetStaticMeshComponent");
}

void ACWeapon::BeginPlay()
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

void ACWeapon::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

// 무기 장착 몽타주 실행 
void ACWeapon::OnEquip()
{
	if(IsValid(GetOwner<ACBaseCharacter>()))
	{
		// 무기를 소유한 캐릭터의 Montage 컴포넌트\를 가져온다.
		UCMontageComponent* montage = Cast<UCMontageComponent>(GetOwner<ACBaseCharacter>()->GetComponentByClass(UCMontageComponent::StaticClass()));
		// 무기가 장착되어 있지 않고, WeaponType이 캐릭터의 WeaponType과 같을 경우
		if (GetOwner<ACBaseCharacter>()->GetWeaponType() == WeaponType) 
		{
			IsEquip = true; // 무기 장착 여부 true
			
			if (IsValid(montage))
			{
				// WeaponType에 맞게 몽타주 실행
				if (WeaponType == EWeaponType::Sword)
				{
					montage->PlayMontage(EMontageType::Equip_Sword);
				}
				else if (WeaponType == EWeaponType::Bow)
				{
					montage->PlayMontage(EMontageType::Equip_Bow);
				}
			} // montage && state
		} // bEquip && GetWeapon == Weapon
	} // GetOwner
}

// 무기 해제
void ACWeapon::OnUnEquip()
{
	if(IsValid(GetOwner<ACBaseCharacter>()))
	{
		UCMontageComponent* montage = Cast<UCMontageComponent>(GetOwner<ACBaseCharacter>()->GetComponentByClass(UCMontageComponent::StaticClass()));
		// 무기가 장착되어 있고, WeaponType이 캐릭터의 WeaponType과 같을 경우
		if (IsEquip && GetOwner<ACBaseCharacter>()->GetWeaponType() == WeaponType)
		{
			IsEquip = false; // 무기 장착 여부 false
			// 무기를 소유한 캐릭터의 Montage 컴포넌트를 가져온다.
			if (IsValid(montage))
			{
				// WeaponType에 맞게 몽타주 실행
				if (WeaponType == EWeaponType::Sword)
				{
					montage->PlayMontage(EMontageType::UnEquip_Sword);
				}
				else if (WeaponType == EWeaponType::Bow)
				{
					montage->PlayMontage(EMontageType::UnEquip_Bow);
				}
			} // montage
		} // bEquip && GetWeapon == Weapon		
	} // GetOwner

}

// 무기를 캐릭터의 Mesh의 입력받은 소켓에 Attach한다.
void ACWeapon::OnAttach(FName InSocketName)
{
	AttachToComponent(GetOwner<ACBaseCharacter>()->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), InSocketName);
}

void ACWeapon::OnAttack()
{
	// 자식 클래스에서 정의
}

void ACWeapon::OnReset()
{
	// 자식 클래스에서 정의
}

void ACWeapon::OnAim()
{
	// 자식 클래스에서 정의
}

void ACWeapon::OffAim()
{
	// 자식 클래스에서 정의
}

void ACWeapon::OnFire()
{
	// 자식 클래스에서 정의
}

void ACWeapon::SpawnDamageText(FVector InLocation, ACBaseCharacter* InHitCharacter, float InDamage, bool InIsDamageEffect)
{
	GetGameInstance<UCGameInstance>()->SpawnDamageText(InLocation, InHitCharacter, InDamage, InIsDamageEffect);
}

EMontageType ACWeapon::GetHitMontageType() const
{
	return UseWeaponDataMaps.Find(AttackType)->HitMontageType;
}



