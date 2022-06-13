#include "Widgets/CDamageText.h"
#include "CUserWidget_DamageText.h"
#include "Components/WidgetComponent.h"

ACDamageText::ACDamageText()
{
	PrimaryActorTick.bCanEverTick = true;

	// 컴포넌트 생성 및 초기화
	Root = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(Root);
	
	// Widget 컴포넌트 생성 및 초기화
	DamageTextWidget = CreateDefaultSubobject<UWidgetComponent>("DamageTextWidget");
	DamageTextWidget->SetupAttachment(Root);
	// WidgetBlueprint'/Game/Widgets/Blueprints/WB_DamageText.WB_DamageText'
	ConstructorHelpers::FClassFinder<UCUserWidget_DamageText> DamageTextWidgetBlueprintClass(TEXT("WidgetBlueprint'/Game/Widgets/Blueprints/WB_DamageText.WB_DamageText_C'"));
	if(DamageTextWidgetBlueprintClass.Succeeded())
	{
		const TSubclassOf<UCUserWidget_DamageText> DamageTextWidgetClass = DamageTextWidgetBlueprintClass.Class;
		DamageTextWidget->SetWidgetClass(DamageTextWidgetClass);
		DamageTextWidget->SetWidgetSpace(EWidgetSpace::Screen);
	}
}

void ACDamageText::BeginPlay()
{
	Super::BeginPlay();

	SetLifeSpan(1.0f);
	
	// 위젯 활성화
	DamageTextWidget->InitWidget();
}

void ACDamageText::SetDamageText(FText InText, bool IsPlayer)
{
	Cast<UCUserWidget_DamageText>(DamageTextWidget->GetWidget())->SetDamageText(InText, IsPlayer);
}

// Called every frame
void ACDamageText::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector location = GetActorLocation();
	SetActorLocation(FVector(location.X, location.Y, location.Z + DeltaTime * 50.0f));

}

