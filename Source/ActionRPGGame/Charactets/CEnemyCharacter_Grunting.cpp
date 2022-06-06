#include "Charactets/CEnemyCharacter_Grunting.h"
#include "ActionRPGGame.h"
#include "CAIController_Grunting.h"
#include "Components/CapsuleComponent.h"
#include "Components/CFootStepSoundComponent.h"
#include "Weapon/CWeapon_Base.h"

ACEnemyCharacter_Grunting::ACEnemyCharacter_Grunting()
{
	// ModelType 초기화
	ModelType = EModelType::Gruntling;

	// AIController 설정
	// Blueprint'/Game/Enemy/Blueprints/Grunting/BP_CAIController_Grunting.BP_CAIController_Grunting'
	ConstructorHelpers::FClassFinder<ACAIController_Grunting> aiControllerBlueprintClass(TEXT("Blueprint'/Game/Enemy/Blueprints/Grunting/BP_CAIController_Grunting.BP_CAIController_Grunting_C'"));
	if(aiControllerBlueprintClass.Succeeded())
	{
		AIControllerClass = aiControllerBlueprintClass.Class;
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

	// Status 데이터 테이블 에셋을 가져와 저장
	// DataTable'/Game/DataTables/DT_Status.DT_Status'
	const ConstructorHelpers::FObjectFinder<UDataTable> statusTableAsset(TEXT("DataTable'/Game/DataTables/DT_Status.DT_Status'"));
	if (statusTableAsset.Succeeded())
	{
		StatusTable = statusTableAsset.Object;
	}

	// OwningWeapon 데이터 테이블 에셋을 가져와 저장
	// DataTable'/Game/DataTables/DT_GrunitingOwningWeapon.DT_GrunitingOwningWeapon'
	const ConstructorHelpers::FObjectFinder<UDataTable> owningWeaponDataTableAsset(TEXT("DataTable'/Game/DataTables/DT_GrunitingOwningWeapon.DT_GrunitingOwningWeapon'"));
	if (owningWeaponDataTableAsset.Succeeded())
	{
		WeaponDataTable = owningWeaponDataTableAsset.Object;
	}
}

void ACEnemyCharacter_Grunting::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(StatusTable))
	{
		// Status 데이터 테이블 값을 저장
		TArray<FStatusData*> statusDatas;
		StatusTable->GetAllRows<FStatusData>("", statusDatas);
		for (FStatusData* data : statusDatas)
		{
			if (data->Type == EStatusType::Enemy_Normal) // Type이 Enemy_Normal 경우
			{
				StatusData = data;
				break;
			}
		}
	}

	// 소유 중인 무기 데이터 테이블 값을 저장
	if(IsValid(WeaponDataTable))
	{
		// 데이터 테이블의 Data를 가져와 owningWeaponDatas에 저장
		TArray<FOwningWeaponData*> owningWeaponDatas;
		WeaponDataTable->GetAllRows<FOwningWeaponData>("", owningWeaponDatas);

		// WeaponType에 맞게 데이터를 저장
		for (int32 i = 0; i < (int32)EWeaponType::Max; i++)
		{
			for (FOwningWeaponData* data : owningWeaponDatas)
			{
				// WeaponType이 같고, bOwning이 true인 경우
				if(data->Type == (EWeaponType)i && data->bOwning == true)
				{
					ACWeapon_Base* weapon = nullptr;
					// WeaponClass가 존재한다면 Actor Spawn
					if(IsValid(data->WeaponClass))
					{
						FTransform transform;
						weapon = GetWorld()->SpawnActorDeferred<ACWeapon_Base>(data->WeaponClass, transform, this);
						weapon->AttachToComponent(GetMesh(),FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), data->WeaponHolsterSocketName);
						UGameplayStatics::FinishSpawningActor(weapon,transform);
					}
					// owningWeapon 구조체 값 설정 
					FEquipedWeaponData equipedWeapon;
					equipedWeapon.Weapon = weapon;
					equipedWeapon.WeaponSocketName = data->WeaponSocketName;
					equipedWeapon.WeaponHolsterSocketName = data->WeaponHolsterSocketName;
					
					EquipedWeaponDataMaps.Add((EWeaponType)i, equipedWeapon); // Map에 추가
				} // if 웨폰 타입 && bOwning
			} // for owningWeaponDatas
		} // for EWeaponType
	}
}

float ACEnemyCharacter_Grunting::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	// TODO : 데미지 
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}
