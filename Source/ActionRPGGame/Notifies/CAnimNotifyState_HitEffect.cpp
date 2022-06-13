#include "Notifies/CAnimNotifyState_HitEffect.h"

FString UCAnimNotifyState_HitEffect::GetNotifyName_Implementation() const
{
	return "HitEffect";
}

void UCAnimNotifyState_HitEffect::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	if (IsValid(MeshComp))
	{
		MeshComp->SetScalarParameterValueOnMaterials("HitEffect", 1.0f);
	}
}

void UCAnimNotifyState_HitEffect::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (IsValid(MeshComp))
	{
		MeshComp->SetScalarParameterValueOnMaterials("HitEffect", 0.0f);
	}
}
