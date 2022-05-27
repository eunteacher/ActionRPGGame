#include "Notifies/CAnimNotify_RightFootStep.h"
#include "Global.h"
#include "Charactets/CBaseCharacter.h"
#include "Components/CFootStepSoundComponent.h"

FString UCAnimNotify_RightFootStep::GetNotifyName_Implementation() const
{
	return "RightFootStep";
}

void UCAnimNotify_RightFootStep::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp != nullptr && MeshComp->GetOwner() != nullptr)
	{
		// Get CFootStepSoundComponent
		UCFootStepSoundComponent* footStepSound = Cast<UCFootStepSoundComponent>(MeshComp->GetOwner()->GetComponentByClass(UCFootStepSoundComponent::StaticClass()));
		if (footStepSound == nullptr)
		{
			CLog::Log("footStepSound == nullptr");
		}
		
		if(footStepSound != nullptr && MeshComp->GetOwner<ACBaseCharacter>() != nullptr)		
		{
			// 현재 SpeedType를 캐릭터를 통해서 가져온다.
			footStepSound->NotifyRightFootStep(MeshComp->GetOwner<ACBaseCharacter>()->GetCurrentSpeedType());
		}
	}
}
