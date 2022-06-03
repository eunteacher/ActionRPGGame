#include "Weapon/CWeapon_Sword.h"
#include "ActionRPGGame.h"
#include "Charactets/CBaseCharacter.h"
#include "Types/CEnumTypes.h"
#include "Components/CapsuleComponent.h"
#include "Components/CMontageComponent.h"
#include "Components/CSoundComponent.h"
#include "Components/CStateComponent.h"

ACWeapon_Sword::ACWeapon_Sword()
{
	// 멤버 변수 초기화
	Weapon = EWeaponType::Sword;
	CanCombo = false;
	IsAttack = false;

	// StaticMesh 컴포넌트 생성
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	StaticMesh->SetupAttachment(Root);
	// StaticMesh'/Game/Weapons/Meshes/SM_sword.SM_sword'
	const ConstructorHelpers::FObjectFinder<UStaticMesh> staticMeshAsset(TEXT("StaticMesh'/Game/Weapons/Meshes/SM_sword.SM_sword'"));
	if(staticMeshAsset.Succeeded())
	{
		UStaticMesh* staticMesh = staticMeshAsset.Object;
		StaticMesh->SetStaticMesh(staticMesh);
		StaticMesh->SetCollisionProfileName("NoCollision");
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
	CLog::Log("OnCollision");
	Capsule->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void ACWeapon_Sword::OffCollision()
{
	CLog::Log("OffCollision");
	Capsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ACWeapon_Sword::OnReset()
{
	CLog::Log("OnReset");
	CanCombo = false;
	IsAttack = false;
	AttackType = EAttackType::Sword_Combo1;
}

void ACWeapon_Sword::OnAttack()
{
	CLog::Log("OnAttack");
	
	// 장착되어 있을 경우
	if(IsEquip)
	{
		if(!IsAttack) // IsAttack이 false인 경우
		{
			// 콤보 공격 사용을 위해서 IsAttack을 true로 변경하여 다시 못들어오게 한다.
			IsAttack = true; 
			// 공격 타입을 콤보 공격 1로 설정
			AttackType = EAttackType::Sword_Combo1;
		
			// AttackType에 따라 Data 저장
			const FWeaponData* data = WeaponData[(int32)AttackType];
			UCMontageComponent* montage = Cast<UCMontageComponent>(GetOwner<ACBaseCharacter>()->GetComponentByClass(UCMontageComponent::StaticClass()));
			UCSoundComponent* sound = Cast<UCSoundComponent>(GetOwner<ACBaseCharacter>()->GetComponentByClass(UCSoundComponent::StaticClass()));

			if(data != nullptr && IsValid(montage) && IsValid(sound))
			{
				// AttackType에 맞는 몽타주 실행
				montage->PlayMontage(GetOwner<ACBaseCharacter>()->GetModelType(), data->Type[AttackType]);
				// Battle 사운드 실행
				sound->PlayAttackSound();
				// TODO : HitEffect와 Damage
			}			
		}
		else
		{
			// 공격 호출이 들어왓기 때문에 CanCombo를 true
			CanCombo = true;
		}
	}
}

void ACWeapon_Sword::ComboAttack()
{
	// CanCombo true인 경우
	if(CanCombo)
	{
		// 다시 못들어오게 하기 위해 CanCombo를 false
		CanCombo = false;
		
		if(AttackType == EAttackType::Sword_Combo1)
		{
			AttackType = EAttackType::Sword_Combo2;
		}
		else if(AttackType == EAttackType::Sword_Combo2)
		{
			AttackType = EAttackType::Sword_Combo3;
		}

		// AttackType에 따라 Data 저장
		const FWeaponData* data = WeaponData[(int32)AttackType];
		UCMontageComponent* montage = Cast<UCMontageComponent>(GetOwner<ACBaseCharacter>()->GetComponentByClass(UCMontageComponent::StaticClass()));
		UCSoundComponent* sound = Cast<UCSoundComponent>(GetOwner<ACBaseCharacter>()->GetComponentByClass(UCSoundComponent::StaticClass()));

		if(data != nullptr && IsValid(montage) && IsValid(sound))
		{
			// AttackType에 맞는 몽타주 실행
			montage->PlayMontage(GetOwner<ACBaseCharacter>()->GetModelType(), data->Type[AttackType]);
			// Battle 사운드 실행
			sound->PlayAttackSound();
			// TODO : HitEffect와 Damage
		}
	}
}

