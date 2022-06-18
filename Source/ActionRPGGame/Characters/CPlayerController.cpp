#include "Characters/CPlayerController.h"
#include "ActionRPGGame.h"
#include "Blueprint/UserWidget.h"
#include "Widgets/CUserWidget_HUD.h"

// 생성자
ACPlayerController::ACPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;

	// UserWidgetHUD 클래스 초기화
	// WidgetBlueprint'/Game/Widgets/Blueprints/WB_HUD.WB_HUD'
	static ConstructorHelpers::FClassFinder<UCUserWidget_HUD> userWidgetHUDClass(TEXT("WidgetBlueprint'/Game/Widgets/Blueprints/WB_HUD.WB_HUD_C'"));
	if (userWidgetHUDClass.Succeeded())
	{
		//CLog::Log("Input HUD Class");
		UserWidgetHUDClass = userWidgetHUDClass.Class;
	}
}

// BeginPlay
void ACPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(UserWidgetHUDClass))
	{
		// 위젯 생성
		UserWidgetHUD = CreateWidget<UCUserWidget_HUD>(this, UserWidgetHUDClass);
		if (IsValid(UserWidgetHUD))
		{
			UserWidgetHUD->AddToViewport();
		}
	}

}

// Tick
void ACPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

