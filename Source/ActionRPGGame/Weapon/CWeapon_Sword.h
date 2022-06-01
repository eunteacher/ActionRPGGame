#pragma once

#include "CoreMinimal.h"
#include "Weapon/CWeapon_Base.h"
#include "CWeapon_Sword.generated.h"

// 전방 선언
class UCapsuleComponent;

UCLASS()
class ACTIONRPGGAME_API ACWeapon_Sword : public ACWeapon_Base
{
	GENERATED_BODY()

public:
	ACWeapon_Sword();

	// Capsule 충돌 켜기
	void OnCollision();
	// Capsule 충돌 끄기
	void OffCollision();
protected:
	// BeginPlay()
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleDefaultsOnly, Category = "Collision")
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleDefaultsOnly, Category = "Collision")
	UCapsuleComponent* Capsule;

private:
	int32 ComboCount; // 콤보 카운터

};
