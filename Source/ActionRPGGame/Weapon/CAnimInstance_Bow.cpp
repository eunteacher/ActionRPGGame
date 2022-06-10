#include "Weapon/CAnimInstance_Bow.h"
#include "ActionRPGGame.h"
#include "Charactets/CBaseCharacter.h"
#include "CWeapon_Far.h"
#include "Types/CEnumTypes.h"

void UCAnimInstance_Bow::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if(IsValid(OwnerCharacter))
	{
		// OwnerCharcter의 WeaponType을 가져온다.
		EWeaponType weaponType = OwnerCharacter->GetWeaponType();
		if(weaponType == EWeaponType::Bow) // 웨폰 타입이 Bow일 경우
		{
			// OwnerCharacter에서 Weapon 클래스를 가져와 IsOverDraw를 저장한다.
			IsOverDraw = Cast<ACWeapon_Far>(OwnerCharacter->GetEquipedWeaponDataMaps().Find(weaponType)->Weapon)->GetIsOverDraw();
			if (IsOverDraw)
			{
				// IsOverDraw가 true일 경우 
				BowCharge = UKismetMathLibrary::FInterpTo(BowCharge, 1.0f, DeltaSeconds, 1.0f);
			}
			else
			{
				BowCharge = 0.0f;
			}
		}
	}
}

// 멤버변수 초기화
void UCAnimInstance_Bow::InitAnimInstance(ACBaseCharacter* InOwnerCharacter)
{
	CLog::Log("AnimInstance_Bow Init()");
	OwnerCharacter = InOwnerCharacter;
	BowCharge = 0.0f;
	IsOverDraw = false;
}
