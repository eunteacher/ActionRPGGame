#pragma once

#include "CoreMinimal.h"
#include "Weapon/CWeapon_Near.h"
#include "CWeapon_Near_Hammer.generated.h"

UCLASS()
class ACTIONRPGGAME_API ACWeapon_Near_Hammer : public ACWeapon_Near
{
	GENERATED_BODY()
public:
	ACWeapon_Near_Hammer();

	virtual void Tick(float DeltaSeconds) override;

	virtual void GetStaticMeshComponent(UStaticMeshComponent*& OutStaticMeshComponent) override;

protected:
	// StaticMesh 컴포넌트, 무기의 Mesh
	UPROPERTY(VisibleDefaultsOnly, Category = "Component")
	UStaticMeshComponent* HammerStaticMesh;

	


};
