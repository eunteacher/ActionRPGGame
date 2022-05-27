#include "Charactets/CPlayerCharacter.h"
#include "Global.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "Components/WidgetComponent.h"
#include "Components/CSoundComponent.h"
#include "Components/CMontageComponent.h"

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

	if(Sound != nullptr)
	{
		// 모델 타입 정의
		Sound->SetModelType(EModelType::GhostLady);
	}
}
// BeginPlay
void ACPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ACPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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
	if (Controller != nullptr && InValue != 0.0f)
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
	if (Controller != nullptr && InValue != 0.0f)
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

void ACPlayerCharacter::OnJump()
{
	CLog::Log("OnJump()");
	// 앉은 상태에서는 점프를 할 수 없음
	// if (State->GetCurrentStateType() != EStateType::Crouch)
	// {
	// 	// bEnableDoubleJump은 Jump 애니메이션에서 노티파티 스테이트로 구간을 설정하여 Begin()에서 true End()에서 false
	// 	if (!bEnableDoubleJump && State->GetCurrentStateType() != EStateType::DoubleJump)
	// 	{
	// 		State->SetJump();
	// 	}
	// 	else
	// 	{
	// 		// DoubleJump 몽타주 및 Sound 실행
	// 		if (State->GetCurrentStateType() != EStateType::DoubleJump)
	// 		{
	// 			State->SetDoubleJump();
	// 		}
	// 	}
	// }
}
// StopJumping() 호출
void ACPlayerCharacter::OffJump()
{
	StopJumping();
}
// 걷기로 변환
void ACPlayerCharacter::OnWalk()
{
	CLog::Log("OnWalk()");
	SetMaxSpeed(ESpeedType::Walk);
}
// 뛰기로 변환
void ACPlayerCharacter::OnRun()
{
	CLog::Log("OnRun()");
	SetMaxSpeed(ESpeedType::Run);
}
// 앉기로 변환
void ACPlayerCharacter::OnCrouch()
{
	CLog::Log("OnCrouch");
	// State->SetCrouch();
}

void ACPlayerCharacter::OffCrouch()
{
	CLog::Log("OffCrouch");
	// State->SetIdle();
}
// 피하기로 변환
void ACPlayerCharacter::OnEvade()
{
	CLog::Log("OnEvade");
	// State->SetEvade();
}


