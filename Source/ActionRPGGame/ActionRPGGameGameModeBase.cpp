#include "ActionRPGGameGameModeBase.h"
#include "Charactets/CPlayerController.h"

AActionRPGGameGameModeBase::AActionRPGGameGameModeBase()
{
	// Blueprint'/Game/Characters/Blueprints/BP_CPlayerCharacter.BP_CPlayerCharacter'
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBlueprintClass(TEXT("Blueprint'/Game/Characters/Blueprints/BP_CPlayerCharacter.BP_CPlayerCharacter_C'"));
	if (PlayerPawnBlueprintClass.Succeeded())
	{
		DefaultPawnClass = PlayerPawnBlueprintClass.Class;
	}

	// Blueprint'/Game/Characters/Blueprints/BP_CPlayerController.BP_CPlayerController'
	static ConstructorHelpers::FClassFinder<ACPlayerController> PlayerControllerBlueprintClass(TEXT("Blueprint'/Game/Characters/Blueprints/BP_CPlayerController.BP_CPlayerController_C'"));
	if (PlayerControllerBlueprintClass.Succeeded())
	{
		PlayerControllerClass = PlayerControllerBlueprintClass.Class;
	}
}
