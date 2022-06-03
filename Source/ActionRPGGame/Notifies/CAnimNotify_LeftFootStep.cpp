#include "Notifies/CAnimNotify_LeftFootStep.h"
#include "ActionRPGGame.h"
#include "Charactets/CBaseCharacter.h"
#include "Components/CFootStepSoundComponent.h"

FString UCAnimNotify_LeftFootStep::GetNotifyName_Implementation() const
{
	return "LeftFootStep";
}

void UCAnimNotify_LeftFootStep::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (IsValid(MeshComp) && IsValid(MeshComp->GetOwner<ACBaseCharacter>()))
	{
		// Get CFootStepSoundComponent
		UCFootStepSoundComponent* footStepSound = Cast<UCFootStepSoundComponent>(MeshComp->GetOwner<ACBaseCharacter>()->GetComponentByClass(UCFootStepSoundComponent::StaticClass()));
		if (footStepSound == nullptr)
		{
			CLog::Log("footStepSound == nullptr");
		}
		
		if(IsValid(footStepSound))		
		{
			// 현재 SpeedType를 캐릭터를 통해서 가져온다.
			footStepSound->NotifyLeftFootStep(MeshComp->GetOwner<ACBaseCharacter>()->GetSpeedType());
		}
	}
}
