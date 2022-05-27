#include "Charactets/CPlayerController.h"
#include "Global.h"
#include "CHUD.h"
#include "GameFramework/Character.h"

// 생성자
ACPlayerController::ACPlayerController()
	: APlayerController()
{
	PrimaryActorTick.bCanEverTick = true;

	// 데이터 테이블 에셋을 가져와 StatusDataTable 초기화
	// DataTable'/Game/DataTables/DT_Status.DT_Status'
	static ConstructorHelpers::FObjectFinder<UDataTable> StatusDataTableAsset(TEXT("DataTable'/Game/DataTables/DT_Status.DT_Status'"));
	if (StatusDataTableAsset.Succeeded())
	{
		StatusDataTable = StatusDataTableAsset.Object;
	}
}
// BeginPlay
void ACPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// StatusTable의 값을 가져와 Status 값 초기화
	if (StatusDataTable != nullptr)
	{
		TArray<FStatusData*> statusDatas;
		StatusDataTable->GetAllRows<FStatusData>("", statusDatas);

		for (FStatusData* data : statusDatas)
		{
			if (data->Type == EStatusType::Player) // StatusType이 Player일 경우
				{
				Health = data->Health;
				MaxHealth = data->MaxHealth;
				Mana = data->Mana;
				MaxMana = data->MaxMana;
				Stamina = data->Stamina;
				MaxStamina = data->MaxStamina;
				}
		}
	}
}
// Tick
void ACPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// TODO : Walk일 경우 스테미너 증가, Run일 경우 스테미너 감소
	// if (Status != nullptr)
	// {
	// 	if (Status->GetCurrentSpeedType() == ESpeedType::Walk)
	// 	{
	// 		Status->AddStamina(50.0f * DeltaTime);
	// 	}
	// 	else if (Status->GetCurrentSpeedType() == ESpeedType::Run)
	// 	{
	// 		// Stamina가 MaxStamina의 10%보다 작을 경우
	// 		if (Status->Stamina < Status->MaxStamina * 0.1f)
	// 		{
	// 			OnWalk();
	// 		}
	//
	// 		Status->SubtractStamina(100.0f * DeltaTime);
	// 	}
	// }
}

void ACPlayerController::AddHealth(float InValue)
{
	// Health 값에 InValue를 더한다.
	Health += InValue;
	// Health의 값을 최소 0.0f, 최대 MaxHealth 
	Health = FMath::Clamp(Health, 0.0f, MaxHealth);
}

void ACPlayerController::SubtractHealth(float InValue)
{
	// Health 값에 InValue를 뺀다.
	Health -= InValue;
	// Health의 값을 최소 0.0f, 최대 MaxHealth 
	Health = FMath::Clamp(Health, 0.0f, MaxHealth);
}

void ACPlayerController::AddMana(float InValue)
{
	// Mana 값에 InValue를 더한다.
	Mana += InValue;
	// Mana의 값을 최소 0.0f, 최대 MaxMana 
	Mana = FMath::Clamp(Mana, 0.0f, MaxMana);
}

void ACPlayerController::SubtractMana(float InValue)
{
	// Mana 값에 InValue를 뺀다.
	Mana -= InValue;
	// Mana의 값을 최소 0.0f, 최대 MaxMana
	Mana = FMath::Clamp(Mana, 0.0f, MaxMana);
}

void ACPlayerController::AddStamina(float InValue)
{
	// Stamina 값에 InValue를 더한다.
	Stamina += InValue;
	// Stamina의 값을 최소 0.0f, 최대 MaxStamina 
	Stamina = FMath::Clamp(Stamina, 0.0f, MaxStamina);
}

void ACPlayerController::SubtractStamina(float InValue)
{
	// Stamina 값에 InValue를 뺀다.
	Stamina -= InValue;
	// Stamina의 값을 최소 0.0f, 최대 MaxStamina 
	Stamina = FMath::Clamp(Stamina, 0.0f, MaxStamina);
}

void ACPlayerController::OnHealthChanged(float InHealth, float InMaxHealth)
{
	GetHUD<ACHUD>()->NotifyHealth(InHealth,InMaxHealth);
}

void ACPlayerController::OnManaChanged(float InMana, float InMaxMana)
{
	GetHUD<ACHUD>()->NotifyStamina(InMana, InMaxMana);
}

void ACPlayerController::OnStaminaChanged(float InStamina, float InMaxStamina)
{
	GetHUD<ACHUD>()->NotifyStamina(InStamina, InMaxStamina);
}
