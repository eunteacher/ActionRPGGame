#include "CHUD.h"
#include "Global.h"
#include "Widgets/CUserWidget_HUD.h"
#include "Widgets/CUserWidget_BaseProgressBar.h"

ACHUD::ACHUD()
{
	// UserWidgetHUD 클래스 초기화
	// WidgetBlueprint'/Game/Widgets/Blueprints/WB_HUD.WB_HUD'
	static ConstructorHelpers::FClassFinder<UCUserWidget_HUD> userWidgetHUDClass(TEXT("WidgetBlueprint'/Game/Widgets/Blueprints/WB_HUD.WB_HUD_C'"));
	if (userWidgetHUDClass.Succeeded())
	{
		//CLog::Log("Input HUD Class");
		UserWidgetHUDClass = userWidgetHUDClass.Class;
	}
}

void ACHUD::BeginPlay()
{
	Super::BeginPlay();

	CLog::Log("HUD BeginPlay");
	if (UserWidgetHUDClass != nullptr)
	{
		// 위젯 생성
		UserWidgetHUD = CreateWidget<UCUserWidget_HUD>(GetOwningPlayerController(), UserWidgetHUDClass);
		if (UserWidgetHUD != nullptr)
		{
			UserWidgetHUD->AddToViewport();
		}
		else
		{
			CLog::Log("UserWidgetHUD Fail");
		}
	}
	else
	{
		CLog::Log("UserWidgetHUDClass Fail");
	}
}

void ACHUD::NotifyStamina(float InValue, float InMaxValue)
{
	// WidgetHUD 함수 호출
	UserWidgetHUD->UpdateStamina(InValue, InMaxValue);
}

void ACHUD::NotifyHealth(float InValue, float InMaxValue)
{
	// WidgetHUD 함수 호출
	UserWidgetHUD->UpdateHealth(InValue, InMaxValue);
}

void ACHUD::NotifyMana(float InValue, float InMaxValue)
{
	// WidgetHUD 함수 호출
	UserWidgetHUD->UpdateMana(InValue, InMaxValue);
}


