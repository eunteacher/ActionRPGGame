#include "Weapon/CWeapon.h"
#include "ActionRPGGame.h"
#include "Characters/CBaseCharacter.h"
#include "Components/CMontageComponent.h"
#include "Types/CEnumTypes.h"
#include "Widgets/CDamageText.h"

ACWeapon::ACWeapon()
{
	PrimaryActorTick.bCanEverTick = true;

	// 멤버 변수 초기화
	IsEquip = false;
	IsAttack = false;
	
	// 컴포넌트 생성 및 초기화
	Root = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(Root);

	// Blueprint'/Game/Widgets/Blueprints/BP_CDamageText.BP_CDamageText'
	ConstructorHelpers::FClassFinder<ACDamageText> damageTextClass(TEXT("Blueprint'/Game/Widgets/Blueprints/BP_CDamageText.BP_CDamageText_C'"));
	if(damageTextClass.Succeeded())
	{
		DamageTextClass = damageTextClass.Class;
	}
}

void ACWeapon::GetStaticMeshComponent(UStaticMeshComponent*& OutStaticMeshComponent)
{
	CLog::Log("ACWeapon_Base GetStaticMeshComponent");
}

void ACWeapon::BeginPlay()
{
	Super::BeginPlay();

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
		if (GetOwner<ACBaseCharacter>()->GetWeaponType() == Weapon) 
		{
			IsEquip = true; // 무기 장착 여부 true
			
			if (IsValid(montage))
			{
				// WeaponType에 맞게 몽타주 실행
				if (Weapon == EWeaponType::Sword)
				{
					montage->PlayMontage(EMontageType::Equip_Sword);
				}
				else if (Weapon == EWeaponType::Bow)
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
		if (IsEquip && GetOwner<ACBaseCharacter>()->GetWeaponType() == Weapon)
		{
			IsEquip = false; // 무기 장착 여부 false
			// 무기를 소유한 캐릭터의 Montage 컴포넌트를 가져온다.
			if (IsValid(montage))
			{
				// WeaponType에 맞게 몽타주 실행
				if (Weapon == EWeaponType::Sword)
				{
					montage->PlayMontage(EMontageType::UnEquip_Sword);
				}
				else if (Weapon == EWeaponType::Bow)
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

EMontageType ACWeapon::GetHitMontageType() const
{
	return UseWeaponDataMaps.Find(AttackType)->HitMontageType;
}



