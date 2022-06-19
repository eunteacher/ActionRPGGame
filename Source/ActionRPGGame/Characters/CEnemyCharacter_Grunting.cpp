#include "Characters/CEnemyCharacter_Grunting.h"
#include "ActionRPGGame.h"
#include "CAIController_Grunting.h"
#include "Components/CapsuleComponent.h"
#include "Components/CFootStepSoundComponent.h"
#include "Patrols//CPatrolComponent.h"
#include "Components/WidgetComponent.h"
#include "Weapon/CWeapon.h"
#include "Widgets/CUserWidget_BaseProgressBar.h"

ACEnemyCharacter_Grunting::ACEnemyCharacter_Grunting()
{
	// ModelType 초기화
	ModelType = EModelType::Grunting;
	StatusType = EStatusType::Enemy_Grunting;
	WeaponType = EWeaponType::Hammer;
	
	// AIController 설정
	// Blueprint'/Game/Enemy/Blueprints/Grunting/BP_CAIController_Grunting.BP_CAIController_Grunting'
	ConstructorHelpers::FClassFinder<ACAIController_Grunting> aiControllerBlueprintClass(TEXT("Blueprint'/Game/Enemy/Blueprints/Grunting/BP_CAIController_Grunting.BP_CAIController_Grunting_C'"));
	if(aiControllerBlueprintClass.Succeeded())
	{
		AIControllerClass = aiControllerBlueprintClass.Class;
		AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	}
	
	// Capsule 컴포넌트 반경 설정
	GetCapsuleComponent()->SetCapsuleRadius(40.0f);
	// Mesh 기본값 설정
	GetMesh()->SetRelativeLocation(FVector(-20.0f, 0.0f, -90.0f));
	GetMesh()->SetRelativeRotation(FRotator(0.0f, 270.0f, 0.0f));
	GetMesh()->SetRelativeScale3D(FVector(1.25f,1.25f,1.5f));

	// 스켈레톤 메시 생성
	// SkeletalMesh'/Game/Enemy/Meshs/SK_Exodus_Gruntling.SK_Exodus_Gruntling'
	const ConstructorHelpers::FObjectFinder<USkeletalMesh> skeletalMeshAsset(TEXT("SkeletalMesh'/Game/Enemy/Meshs/SK_Exodus_Gruntling.SK_Exodus_Gruntling'"));
	if (skeletalMeshAsset.Succeeded())
	{
		//CLog::Log("meshAsset.Succeeded()");
		USkeletalMesh* mesh = skeletalMeshAsset.Object;
		GetMesh()->SetSkeletalMesh(mesh);
	}
	// AnimInstance 생성 및 초기화
	// AnimBlueprint'/Game/Enemy/Animations/Grunting/ABP_Enemy_Gruniting.ABP_Enemy_Gruniting'
	ConstructorHelpers::FClassFinder<UAnimInstance> animInstanceClass(TEXT("AnimBlueprint'/Game/Enemy/Animations/Grunting/ABP_Enemy_Gruniting.ABP_Enemy_Gruniting_C'"));
	if (animInstanceClass.Succeeded())
	{
		const TSubclassOf<UAnimInstance> animInstance = animInstanceClass.Class;
		GetMesh()->SetAnimInstanceClass(animInstance);
	}

	// Widget 컴포넌트 생성 및 초기화
	HealthBarWidget = CreateDefaultSubobject<UWidgetComponent>("HealthBar");
	HealthBarWidget->SetupAttachment(GetMesh());
	ConstructorHelpers::FClassFinder<UCUserWidget_BaseProgressBar> healthBarWidgetBlueprintClass(TEXT("WidgetBlueprint'/Game/Widgets/Blueprints/WB_Enemy_HealthBar.WB_Enemy_HealthBar_C'"));
	if(healthBarWidgetBlueprintClass.Succeeded())
	{
		const TSubclassOf<UCUserWidget_BaseProgressBar> healthBarWidgetClass = healthBarWidgetBlueprintClass.Class;
		HealthBarWidget->SetWidgetClass(healthBarWidgetClass);
		HealthBarWidget->SetRelativeLocation(FVector(0.0f, 0.0f, 100.0f));
		HealthBarWidget->SetDrawSize(FVector2D(100.0f, 10.0f));
		HealthBarWidget->SetWidgetSpace(EWidgetSpace::Screen);
	}

	// Grunting OwningWeapon 데이터 테이블 에셋을 가져와 저장
	// DataTable'/Game/DataTables/DT_GrunitingOwningWeapon.DT_GrunitingOwningWeapon'
	const ConstructorHelpers::FObjectFinder<UDataTable> GruntingWeaponDataTableAsset(TEXT("DataTable'/Game/DataTables/DT_GrunitingOwningWeapon.DT_GrunitingOwningWeapon'"));
	if (GruntingWeaponDataTableAsset.Succeeded())
	{
		WeaponTable = GruntingWeaponDataTableAsset.Object;
	}

	// Patrol 컴포넌트 생성
	Patrol = CreateDefaultSubobject<UCPatrolComponent>("Patrol");
}

void ACEnemyCharacter_Grunting::BeginPlay()
{
	Super::BeginPlay();

	// 데이터 테이블의 값을 저장할 배열
	TArray<FOwningWeaponData*> owningWeaponDatas;
	WeaponTable->GetAllRows<FOwningWeaponData>("", owningWeaponDatas);

	// WeaponType에 맞게 데이터를 저장
	for (int32 i = 0; i < (int32)EWeaponType::Max; i++)
	{
		for (FOwningWeaponData* data : owningWeaponDatas)
		{
			// WeaponType이 같고, bOwning이 true인 경우
			if(data->Type == (EWeaponType)i && data->bOwning == true)
			{
				ACWeapon* weapon = nullptr;
				// WeaponClass가 존재한다면 Actor Spawn
				if(IsValid(data->WeaponClass))
				{
					FTransform transform;
					weapon = GetWorld()->SpawnActorDeferred<ACWeapon>(data->WeaponClass, transform, this);
					weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), data->WeaponHolsterSocketName);
					UGameplayStatics::FinishSpawningActor(weapon, transform);
				}
				// FEquipedWeaponData 구조체 값 설정 
				FEquipWeaponData equipWeaponData;
				equipWeaponData.Weapon = weapon;
				equipWeaponData.IsAiming = false;
				equipWeaponData.WeaponSocketName = data->WeaponSocketName;
				equipWeaponData.WeaponHolsterSocketName = data->WeaponHolsterSocketName;
				
				EquipWeaponDataMaps.Add((EWeaponType)i, equipWeaponData); // Map에 추가
			} // if 웨폰 타입 && bOwning
		} // for owningWeaponDatas
	} // for EWeaponType

	// 위젯 활성화
	HealthBarWidget->InitWidget();
	Cast<UCUserWidget_BaseProgressBar>(HealthBarWidget->GetWidget())->UpdateValue(UseStatusData.Health, UseStatusData.MaxHealth);

	if(EquipWeaponDataMaps.Contains(WeaponType))
	{
		EquipWeaponDataMaps.Find(WeaponType)->Weapon->OnEquip();
	}
}

float ACEnemyCharacter_Grunting::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	const float damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	return damage;
}
