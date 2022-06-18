#include "Characters/CPlayerCharacter.h"
#include "ActionRPGGame.h"
#include "CGameInstance.h"
#include "CPlayerController.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/CSoundComponent.h"
#include "Components/CMontageComponent.h"
#include "Weapon/CWeapon.h"
#include "Abilities/CAbility.h"

// 생성자 멤버 변수 생성 및 초기화
ACPlayerCharacter::ACPlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// 멤버 변수 초기화
	TurnRate = 45.0f; // 회전 비율
	TeamID = 0;
	ModelType = EModelType::GhostLady; // ModelType 정의
	WeaponType = EWeaponType::Default;
	StatusType = EStatusType::Player;

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

	// OwningWeapon 데이터 테이블 에셋을 가져와 저장
	// DataTable'/Game/DataTables/DT_PlayerOwningWeapon.DT_PlayerOwningWeapon'
	const ConstructorHelpers::FObjectFinder<UDataTable> playerWeaponDataTableAsset(TEXT("DataTable'/Game/DataTables/DT_PlayerOwningWeapon.DT_PlayerOwningWeapon'"));
	if (playerWeaponDataTableAsset.Succeeded())
	{
		WeaponTable = playerWeaponDataTableAsset.Object;
	}

	// DataTable'/Game/DataTables/DT_PlayerOwningAbility.DT_PlayerOwningAbility'
	const ConstructorHelpers::FObjectFinder<UDataTable> playerAbilityDataTableAsset(TEXT("DataTable'/Game/DataTables/DT_PlayerOwningAbility.DT_PlayerOwningAbility'"));
	if (playerAbilityDataTableAsset.Succeeded())
	{
		AbilityTable = playerAbilityDataTableAsset.Object;
	}
}

// BeginPlay
void ACPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	// 데이터 테이블의 값을 저장할 배열
	TArray<FOwningWeaponData*> owningWeaponDatas;
	WeaponTable->GetAllRows<FOwningWeaponData>("", owningWeaponDatas);

	// 무기 생성
	// WeaponType에 맞게 데이터를 저장
	for (int32 i = 0; i < (int32)EWeaponType::Max; i++)
	{
		for (FOwningWeaponData* data : owningWeaponDatas)
		{
			// WeaponType이 같고, bOwning이 true인 경우
			if(data->Type == (EWeaponType)i && data->bOwning == true && IsValid(data->WeaponClass))
			{
				ACWeapon* weapon = nullptr;

				FTransform transform;
				weapon = GetWorld()->SpawnActorDeferred<ACWeapon>(data->WeaponClass, transform, this);
				weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), data->WeaponHolsterSocketName);
				UGameplayStatics::FinishSpawningActor(weapon, transform);

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

	// 데이터 테이블의 값을 저장할 배열 선언
	TArray<FOwningAbilityData*> owningAbilityDatas;
	AbilityTable->GetAllRows<FOwningAbilityData>("", owningAbilityDatas);
	
	// 어빌리티 생성
	for (int32 i = 0; i < (int32)EAbilityType::Max; i++)
	{
		for(FOwningAbilityData* data : owningAbilityDatas)
		{
			if(data->bOwning && IsValid(data->AbilityClass) && data->Type == (EAbilityType)i)
			{
				ACAbility* ability = nullptr;
				FTransform transform;
				ability = GetWorld()->SpawnActorDeferred<ACAbility>(data->AbilityClass, transform, this);
				ability->AttachToComponent(GetMesh(),FAttachmentTransformRules(EAttachmentRule::KeepRelative, true));
				ability->InitAbility(this, EquipWeaponDataMaps.Find(ability->GetWeaponType())->Weapon);
				UGameplayStatics::FinishSpawningActor(ability, transform);

				FEquipAbilityData equipAbilityData;
				equipAbilityData.Ability = ability;
			
				EquipAbilityDataMaps.Add((EAbilityType)i, equipAbilityData);
			} // if bOwning && IsValid abilityClass
		} // for data
	}
}

float ACPlayerCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	UseStatusData.Health -= damage;
	if(UseStatusData.Health < 0.0f)
	{
		// TODO : Dead
		OnDead();
	}
	
	UpdateHealth(UseStatusData.Health, UseStatusData.MaxHealth);
	return damage;
}

// Tick
void ACPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 뛰기 상태일 경우 
	if (SpeedType == ESpeedType::Run)
	{
		// MaxStamina의 10%보다 작을 경우 OnWalk()
		if (UseStatusData.Stamina < UseStatusData.MaxStamina * 0.1f)
		{
			OnWalk();
		}
		else
		{
			// 스테미너 감소
			UseStatusData.Stamina = UKismetMathLibrary::FClamp(UseStatusData.Stamina - 100.0f * DeltaTime, 0.0f, UseStatusData.MaxStamina);
			UpdateStamina(UseStatusData.Stamina, UseStatusData.MaxStamina);
		}
	}
	else
	{
		// 뛰기 상태가 아니라면 스테미너 증가
		UseStatusData.Stamina = UKismetMathLibrary::FClamp(UseStatusData.Stamina + 50.0f * DeltaTime, 0.0f, UseStatusData.MaxStamina);
		UpdateStamina(UseStatusData.Stamina, UseStatusData.MaxStamina);
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

	PlayerInputComponent->BindAction("Equip", IE_Pressed, this, &ACPlayerCharacter::OnEquip);
	PlayerInputComponent->BindAction("UnEquip", IE_Pressed, this, &ACPlayerCharacter::OnUnEquip);

	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &ACPlayerCharacter::OnAttack);

	PlayerInputComponent->BindAction("Aim", IE_Pressed, this, &ACPlayerCharacter::OnAim);
	PlayerInputComponent->BindAction("Aim", IE_Released, this, &ACPlayerCharacter::OffAim);

	PlayerInputComponent->BindAction("Ability01", IE_Pressed, this, &ACPlayerCharacter::OnAbility01);
	PlayerInputComponent->BindAction("Ability02", IE_Pressed, this, &ACPlayerCharacter::OnAbility02);
	PlayerInputComponent->BindAction("Ability03", IE_Pressed, this, &ACPlayerCharacter::OnAbility03);
	PlayerInputComponent->BindAction("Ability04", IE_Pressed, this, &ACPlayerCharacter::OnAbility03);

}

void ACPlayerCharacter::SetDefaultWeapon()
{
	Super::SetDefaultWeapon();

	// TODO : 아이콘 변경
	if(IsValid(GetController<ACPlayerController>()))
	{
		if(GetController<ACPlayerController>()->OnWeaponChanged.IsBound())
		{
			UTexture2D* weaponIcon = nullptr;
			TArray<ACAbility*> abilitySlots;
			GetController<ACPlayerController>()->OnWeaponChanged.Broadcast(weaponIcon, abilitySlots, true);
		}
	}
}

void ACPlayerCharacter::MoveForward(float InValue)
{
	if (IsValid(GetController<ACPlayerController>()) && InValue != 0.0f)
	{
		// 컨트롤러의 Yaw 값
		const FRotator rotation = GetController<ACPlayerController>()->GetControlRotation(); // 컨트롤러의 회전 값
		const FRotator yawRotation(0, rotation.Yaw, 0);

		const FVector direction = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X); // 행렬의 x축
		AddMovementInput(direction, InValue);
	}
}

void ACPlayerCharacter::MoveRight(float InValue)
{
	if (IsValid(GetController<ACPlayerController>()) && InValue != 0.0f)
	{
		// 컨트롤러의 Yaw 값
		const FRotator rotation = GetController<ACPlayerController>()->GetControlRotation();
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
		// PlaySound
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
			Montage->PlayMontage(montageType); // 몽타주 실행
			Sound->PlayEvadeSound(); // 사운드 실행

			FVector direction; // 구르기 방향
			// MontageType에 따라 방향 결정
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

void ACPlayerCharacter::OnEquip()
{
	CLog::Log("OnEquip");

	// Weapon Type에 따라 Equip 순서
	// Default -> Sword, Sword -> Bow, Bow -> Sword
	if (WeaponType == EWeaponType::Default)
	{
		WeaponType = EWeaponType::Sword;
	}
	else
	{
		// 현재 WeaponType을 Map이 Key로 포함되어 있다면 현재 무기를 장착 해제한다.
		if(EquipWeaponDataMaps.Contains(WeaponType))
		{
			// 현재 무기를 Holster로 Attach한다.
			EquipWeaponDataMaps.Find(WeaponType)->Weapon->OnAttach(EquipWeaponDataMaps.Find(WeaponType)->WeaponHolsterSocketName);
		}
		
		// 현재 WeaponType을 변경한다.
		if(WeaponType == EWeaponType::Sword)
		{
			WeaponType = EWeaponType::Bow;
		}
		else if(WeaponType == EWeaponType::Bow)
		{
			WeaponType = EWeaponType::Sword;
		}
	}

	// 현재 WeaponType을 Map이 Key로 포함되어 있다면
	if(EquipWeaponDataMaps.Contains(WeaponType))
	{
		// Weapon의 OnEquip() 호출
		EquipWeaponDataMaps.Find(WeaponType)->Weapon->OnEquip();

		// Ability Slot 변경
		if(IsValid(GetController<ACPlayerController>()))
		{
			if(GetController<ACPlayerController>()->OnWeaponChanged.IsBound())
			{
				// OnWeaponChanged의 매개변수 선언 및 정의 
				UTexture2D* weaponIcon = EquipWeaponDataMaps.Find(WeaponType)->Weapon->GetWeaponIcon();
				TArray<ACAbility*> abilities;
				for (int32 i = 0; i < (int32)EAbilityType::Max; i++)
				{
					if (EquipAbilityDataMaps.Contains((EAbilityType)i))
					{
						ACAbility* ability = EquipAbilityDataMaps.Find((EAbilityType)i)->Ability;
						if (ability->GetWeaponType() == WeaponType && ability->GetAbilityType() == (EAbilityType)i)
						{
							abilities.Add(EquipAbilityDataMaps.Find((EAbilityType)i)->Ability);
						} // if weaponType && abilityType
					} // if Contains
				}

				if (GetController<ACPlayerController>()->OnWeaponChanged.IsBound())
				{
					GetController<ACPlayerController>()->OnWeaponChanged.Broadcast(weaponIcon, abilities, false);
				}
			}  // IsBound
		} // IsValid playerController
	}
}

// WeaponType을 Default로 변경
void ACPlayerCharacter::OnUnEquip()
{
	CLog::Log("OnUnEquip");

	// WeaponType이 Default가 아닌 경우만
	if (WeaponType != EWeaponType::Default)
	{
		// 현재 WeaponType을 Map이 Key로 포함되어 있다면
		if (EquipWeaponDataMaps.Contains(WeaponType))
		{
			// Weapon의 OnEquip() 호출
			EquipWeaponDataMaps.Find(WeaponType)->Weapon->OnUnEquip();
		}
	}
}

void ACPlayerCharacter::OnAttack()
{
	// WeaponType이 Default일 때는 공격 함수가 실행되지 않는다.
	if(WeaponType != EWeaponType::Default)
	{
		// 현재 WeaponType을 Map이 Key로 포함되어 있다면
		if(EquipWeaponDataMaps.Contains(WeaponType))
		{
			// Weapon의 OnAttack() 호출
			EquipWeaponDataMaps.Find(WeaponType)->Weapon->OnAttack();
		}		
	}
}

void ACPlayerCharacter::OnAim()
{
	CLog::Log("Player On Aim");
	if(WeaponType == EWeaponType::Bow)
	{
		// 현재 WeaponType을 Map이 Key로 포함되어 있다면
		if(EquipWeaponDataMaps.Contains(WeaponType))
		{
			// Weapon의 OnAim() 호출
			EquipWeaponDataMaps.Find(WeaponType)->IsAiming = true;
			EquipWeaponDataMaps.Find(WeaponType)->Weapon->OnAim();
		}		
	}
}

void ACPlayerCharacter::OffAim()
{
	CLog::Log("Player Off Aim");
	if(WeaponType == EWeaponType::Bow)
	{
		// 현재 WeaponType을 Map이 Key로 포함되어 있다면
		if(EquipWeaponDataMaps.Contains(WeaponType))
		{
			// Weapon의 OffAim() 호출
			EquipWeaponDataMaps.Find(WeaponType)->IsAiming = false;
			EquipWeaponDataMaps.Find(WeaponType)->Weapon->OffAim();
		}		
	}
}

void ACPlayerCharacter::OnAbility01()
{
	CLog::Log("Player OnAbility01");

	if (WeaponType != EWeaponType::Default)
	{
		if (WeaponType == EWeaponType::Sword)
		{
			AbilityType = EAbilityType::FireSword;
		}

		if (EquipAbilityDataMaps.Contains(AbilityType))
		{
			// Update MansBar
			float mana = UseStatusData.Mana - EquipAbilityDataMaps.Find(AbilityType)->Ability->GetManaCost();
			UpdateMana(mana, UseStatusData.MaxMana);

			EquipAbilityDataMaps.Find(AbilityType)->Ability->OnActivation();
		}

	}
}

void ACPlayerCharacter::OnAbility02()
{
	CLog::Log("Player OnAbility02");

	if (WeaponType != EWeaponType::Default)
	{
		if (WeaponType == EWeaponType::Sword)
		{
			AbilityType = EAbilityType::RangeAttack;
		}

		// TODO : Ability 쿨다운, 마나 코스트 
	}

}

void ACPlayerCharacter::OnAbility03()
{
	CLog::Log("Player OnAbility03");

	if (WeaponType != EWeaponType::Default)
	{
		if (WeaponType == EWeaponType::Sword)
		{
			AbilityType = EAbilityType::TakeDown;
		}

		// TODO : Ability 쿨다운, 마나 코스트 
	}

}

void ACPlayerCharacter::OnAbility04()
{
	CLog::Log("Player OnAbility04");

	if (WeaponType != EWeaponType::Default)
	{
		if (WeaponType == EWeaponType::Sword)
		{
			AbilityType = EAbilityType::Star;
		}

		// TODO : Ability 쿨다운, 마나 코스트 
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
