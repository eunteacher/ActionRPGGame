#pragma once

#include "CoreMinimal.h"
#include "Weapon/CWeapon_Far.h"
#include "CWeapon_Far_Bow.generated.h"

UCLASS()
class ACTIONRPGGAME_API ACWeapon_Far_Bow : public ACWeapon_Far
{
	GENERATED_BODY()
public:
	ACWeapon_Far_Bow();
	
	virtual void Tick(float DeltaSeconds) override;

	virtual void OnFire() override;
protected:
	virtual void BeginPlay() override;
	
	// 활
	UPROPERTY(VisibleDefaultsOnly,Category="Component")
	USkeletalMeshComponent* SkeletalMesh;

	// 화살 
	UPROPERTY(VisibleDefaultsOnly,Category="Component")
	UStaticMeshComponent* StaticMesh;
};
