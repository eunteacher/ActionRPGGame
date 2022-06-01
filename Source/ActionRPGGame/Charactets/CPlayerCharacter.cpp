#include "Charactets/CPlayerCharacter.h"
#include "ActionRPGGame.h"
#include "CPlayerController.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "Components/WidgetComponent.h"
#include "Components/CSoundComponent.h"
#include "Components/CMontageComponent.h"
#include "Weapon/CWeapon_Sword.h"

ACPlayerCharacter::ACPlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// 멤버 변수 초기화
	TurnRate = 45.0f; // 회전 비율

	// UseControllerRotation 값 설정
	bUseControllerRotationPitch = false;
	// bUseControllerRotationYaw = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	// CharacterMovement 값 설정
	// GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->MaxWalkSpeed = 200.f;
	GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;
	GetCharacterMovement()->MaxWalkSpeedCrouched = 150.0f;

	// SpringArm 생성 및 값 초기화
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->SetRelativeLocation(FVector(0.0f, 0.0f, 90.0f));
	SpringArm->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
	SpringArm->TargetArmLength = 600.0f;
	SpringArm->bUsePawnControlRotation = true;
	//SpringArm->bEnableCameraLag = true;
	//SpringArm->bDoCollisionTest = true;

	// Camera 생성 및 값 초기화
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	Camera->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	Camera->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
	Camera->bUsePawnControlRotation = false;

	// Mesh 기본값 설정
	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));
	GetMesh()->SetRelativeRotation(FRotator(0.0f, 270.0f, 0.0f));

	// 스켈레톤 메시 생성
	// SkeletalMesh'/Game/Characters/Meshs/SK_AssassinA.SK_AssassinA'
	const ConstructorHelpers::FObjectFinder<USkeletalMesh> skeletalMeshAsset(TEXT("SkeletalMesh'/Game/Characters/Meshs/SK_AssassinA.SK_AssassinA'"));
	if (skeletalMeshAsset.Succeeded())
	{
		//CLog::Log("meshAsset.Succeeded()");
		USkeletalMesh* mesh = skeletalMeshAsset.Object;
		GetMesh()->SetSkeletalMesh(mesh);
	}
	// AnimInstance 생성 및 초기화
	// AnimBlueprint'/Game/Characters/Animations/ABP_PlayerCharacter.ABP_PlayerCharacter'
	 ConstructorHelpers::FClassFinder<UAnimInstance> animInstanceClass(TEXT("AnimBlueprint'/Game/Characters/Animations/ABP_PlayerCharacter.ABP_PlayerCharacter_C'"));
	 if (animInstanceClass.Succeeded())
	 {
	 	const TSubclassOf<UAnimInstance> animInstance = animInstanceClass.Class;
	 	GetMesh()->SetAnimInstanceClass(animInstance);
	 }

	// 데이터 테이블 에셋을 가져와 저장
	// DataTable'/Game/DataTables/DT_Status.DT_Status'
	static ConstructorHelpers::FObjectFinder<UDataTable> statusTableAsset(TEXT("DataTable'/Game/DataTables/DT_Status.DT_Status'"));
	if (statusTableAsset.Succeeded())
	{
		StatusTable = statusTableAsset.Object;
	}

	// Weapon 클래스를 가져와 WepaonClass에 저장
	// Blueprint'/Game/Weapons/Blueprints/BP_CWeapon_Sword.BP_CWeapon_Sword'
	ConstructorHelpers::FClassFinder<ACWeapon_Base> nearWeaponBlueprintClass(TEXT("Blueprint'/Game/Weapons/Blueprints/BP_CWeapon_Sword.BP_CWeapon_Sword_C'"));
	if (nearWeaponBlueprintClass.Succeeded())
	{
		NearWeaponClass = nearWeaponBlueprintClass.Class;
	}

	// Weapon 클래스를 가져와 WepaonClass에 저장
	// ConstructorHelpers::FClassFinder<ACWeapon_Base> farWeaponBlueprintClass(TEXT(""));
	// if (farWeaponBlueprintClass.Succeeded())
	// {
	// 	FarWeaponClass = farWeaponBlueprintClass.Class;
	// }
}
// BeginPlay
void ACPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(StatusTable))
	{
		// 데이터 테이블 읽기
		TArray<FStatusData*> statusDatas;
		StatusTable->GetAllRows<FStatusData>("", statusDatas);
		for (FStatusData* data : statusDatas)
		{
			if (data->Type == EStatusType::Player)
			{
				StatusData = data;
			}
		}
	}

	if (IsValid(NearWeaponClass))
	{
		FTransform transform;
		NearWeapon = GetWorld()->SpawnActorDeferred<ACWeapon_Sword>
		(
			NearWeaponClass,
			transform,
			this,
			nullptr,
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn
		);
		NearWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, false), FName("Sword"));
		UGameplayStatics::FinishSpawningActor(NearWeapon, transform);
	}
	
}
// Tick
void ACPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(StatusData != nullptr)
	{
		// 뛰기 상태일 경우 
		if(SpeedType == ESpeedType::Run)
		{
			// MaxStamina의 10%보다 작을 경우 OnWalk()
			if(StatusData->Stamina < StatusData->MaxStamina * 0.1f)
			{
				OnWalk();
			}
			else
			{
				// 스테미너 감소 
				StatusData->Stamina -= 100.0f * DeltaTime;
				UpdateStamina(StatusData->Stamina,StatusData->MaxStamina);
			}
		}
		else
		{
			// 뛰기 상태가 아니라면 스테미너 증가
			StatusData->Stamina += 50.0f * DeltaTime;
			UpdateStamina(StatusData->Stamina,StatusData->MaxStamina);
		}		
	}
}

void ACPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Bind Axis
	PlayerInputComponent->BindAxis("MoveForward", this, &ACPlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACPlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("TurnRight", this, &ACPlayerCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &ACPlayerCharacter::LookUpAtRate);

	// Bind Action
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACPlayerCharacter::OnJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACPlayerCharacter::OffJump);

	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ACPlayerCharacter::OnRun);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &ACPlayerCharacter::OnWalk);

	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &ACPlayerCharacter::OnCrouch);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &ACPlayerCharacter::OffCrouch);

	PlayerInputComponent->BindAction("Evade", IE_Pressed, this, &ACPlayerCharacter::OnEvade);
}

void ACPlayerCharacter::MoveForward(float InValue)
{
	if (IsValid(Controller) && InValue != 0.0f)
	{
		// 컨트롤러의 Yaw 값
		const FRotator rotation = Controller->GetControlRotation(); // 컨트롤러의 회전 값
		const FRotator yawRotation(0, rotation.Yaw, 0);

		const FVector direction = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X); // 행렬의 x축
		AddMovementInput(direction, InValue);
	}
}

void ACPlayerCharacter::MoveRight(float InValue)
{
	if (IsValid(Controller) && InValue != 0.0f)
	{
		// 컨트롤러의 Yaw 값
		const FRotator rotation = Controller->GetControlRotation();
		const FRotator yawRotation(0, rotation.Yaw, 0);

		const FVector direction = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Y); // 행렬의 y축
		AddMovementInput(direction, InValue);
	}
}

void ACPlayerCharacter::TurnAtRate(float InRate)
{
	AddControllerYawInput(InRate * TurnRate * GetWorld()->GetDeltaSeconds());
}

void ACPlayerCharacter::LookUpAtRate(float InRate)
{
	AddControllerPitchInput(InRate * TurnRate * GetWorld()->GetDeltaSeconds());
}
// Jump() 호출
void ACPlayerCharacter::OnJump()
{
	if(IsValid(Sound) && !GetCharacterMovement()->IsFalling())
	{
		StateType = EStateType::Jump;
		Sound->PlayJumpSound();
		Jump();
	}
}
	
// StopJumping() 호출
void ACPlayerCharacter::OffJump()
{
	StopJumping();
}
// CBaseCharacter 클래스에 있는 SetMaxSpeed() 호출
void ACPlayerCharacter::OnWalk()
{
	CLog::Log("OnWalk()");
	SetMaxSpeed(ESpeedType::Walk);
}
// CBaseCharacter 클래스에 있는 SetMaxSpeed() 호출
void ACPlayerCharacter::OnRun()
{
	CLog::Log("OnRun()");
	SetMaxSpeed(ESpeedType::Run);
}
// Crouch() 호출
void ACPlayerCharacter::OnCrouch()
{
	CLog::Log("OnCrouch");
	Crouch();
}
// UnCrouch() 호출
void ACPlayerCharacter::OffCrouch()
{
	CLog::Log("OffCrouch");
	UnCrouch();
}
// 캐릭터의 마지막 입력 방향으로 구르기를 실행한다.
void ACPlayerCharacter::OnEvade()
{
	CLog::Log("OnEvade");
	if(!GetCharacterMovement()->IsFalling()) // 공중 상태가 아닐 경우 
	{
		StateType = EStateType::Evade; // StateType 설정
		// 마지막 입력 값을 가져온다.
		FVector inputDirection = GetLastMovementInputVector();
		// 캐릭터의 Forward 벡터와 내적
		float dotForward = UKismetMathLibrary::Dot_VectorVector(GetActorForwardVector(), inputDirection);
		// 캐럭티의 Forward 벡터와 외적
		FVector crossValue = UKismetMathLibrary::Cross_VectorVector(GetActorForwardVector(), inputDirection);
		// 캐릭터의 Up 벡터와 외적의 값을 내적
		float dotUp = UKismetMathLibrary::Dot_VectorVector(GetActorUpVector(), crossValue);

		// 실행할 몽타주 타입 설정
		EMontageType montageType = EMontageType::Max;
		if (dotForward > 0.0f && (dotUp < 0.1f && dotUp > -0.1f))
		{
			CLog::Log("Forward");
			montageType = EMontageType::EvadeForward;
		}
		else if (dotForward < 0.0f && (dotUp < 0.1f && dotUp > -0.1f))
		{
			CLog::Log("Back");
			montageType = EMontageType::EvadeBack;
		}
		else if (dotUp > 0.0f && (dotForward < 0.1f && dotForward > -0.1f))
		{
			CLog::Log("Right");
			montageType = EMontageType::EvadeRight;
		}
		else if (dotUp < 0.0f && (dotForward < 0.1f && dotForward > -0.1f))
		{
			CLog::Log("Left");
			montageType = EMontageType::EvadeLeft;
		}

		if(IsValid(Montage) && IsValid(Sound) && montageType != EMontageType::Max)
		{
			Montage->PlayMontage(ModelType, montageType); // 몽타주 실행
			Sound->PlayEvadeSound(); // 사운드 실행

			FVector direction; // 구르기 방향
			switch (montageType)
			{
			case EMontageType::EvadeForward:
				direction = GetActorForwardVector();
				break;

			case EMontageType::EvadeBack:
				direction = GetActorForwardVector() * -1.0f;
				break;

			case EMontageType::EvadeLeft:
				direction = GetActorRightVector() * -1.0f;
				break;

			case EMontageType::EvadeRight:
				direction = GetActorRightVector();
				break;

			default:
				break;
			}

			FLatentActionInfo info;
			info.CallbackTarget = this;

			FVector evadeLocation = GetActorLocation(); // Evade 도착 위치
			evadeLocation += direction * 300.0f;
			FRotator evadeRotation = GetActorRotation(); // Evade 방향

			// 캐릭터 이동
			UKismetSystemLibrary::MoveComponentTo
			(
				GetCapsuleComponent(),
				evadeLocation,
				evadeRotation,
				false,
				false,
				0.3f,
				false,
				EMoveComponentAction::Move,
				info
			);
		} // if(IsValid(Montage) && IsValid(Sound))
	}
}
// 델리게이트 호출 - Update Health
void ACPlayerCharacter::UpdateHealth(float& InHealth, float& InMaxHealth)
{
	const ACPlayerController* controller = GetController<ACPlayerController>();
	if(IsValid(controller) && controller->OnHealthChanged.IsBound())
	{
		controller->OnHealthChanged.Broadcast(InHealth,InMaxHealth);
	}
}
// 델리게이트 호출 - Update Mana
void ACPlayerCharacter::UpdateMana(float& InMana, float& InMaxMana)
{
	const ACPlayerController* controller = GetController<ACPlayerController>();
	if(IsValid(controller) && controller->OnManaChanged.IsBound())
	{
		controller->OnManaChanged.Broadcast(InMana,InMaxMana);
	}
}
// 델리게이트 호출 - Updata Stamina
void ACPlayerCharacter::UpdateStamina(float& InStamina, float& InMaxStamina)
{
	const ACPlayerController* controller = GetController<ACPlayerController>();
	if(IsValid(controller) && controller->OnStaminaChanged.IsBound())
	{
		controller->OnStaminaChanged.Broadcast(InStamina,InMaxStamina);
	}
}
