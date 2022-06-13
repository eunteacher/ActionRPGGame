#include "Notifies/CAnimNotifyState_Dissolve.h"

FString UCAnimNotifyState_Dissolve::GetNotifyName_Implementation() const
{
	return "Dissolve";
}

void UCAnimNotifyState_Dissolve::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
	if (IsValid(MeshComp))
	{
		MeshComp->SetScalarParameterValueOnMaterials("Dissolve", MeshComp->GetAnimInstance()->GetCurveValue("Dissolve"));
	}
}

void UCAnimNotifyState_Dissolve::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	
}
