
#include "Character/KatanaCharacterBase.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"

#include "Enemy/Abilities/AbilitySystemCompBase.h"

#include "Components/StaticMeshComponent.h"
#include "Item/Item_WeaponBase.h"




AKatanaCharacterBase::AKatanaCharacterBase() : Super(),
MaxGuard(0.0f), bGuardSuperArmour(false), bSkillSuperArmour(false), bSpecialSkillSuperArmour(false),
Current_Player_State(EPlayerActionState::NONE),
Current_Skill_State(EPlayerSkillState::NONE),
bisTryMove(true), bIsAttack(true),
bisTryJump(true), bisRolling(true), bIsattackcount(true), AttackCountNumber(0),
LockOnRange(1000.f), bIsLockOn(false), ElementalAttack(false), ElementalAttack_Icy(false),
StoredRollDirection(FVector::ZeroVector)
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;


	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 1000.f;
	GetCharacterMovement()->AirControl = 0.2f;
}


void AKatanaCharacterBase::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AKatanaCharacterBase::PlayerStartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AKatanaCharacterBase::PlayerStopJump);

	PlayerInputComponent->BindAxis("MoveForward", this, &AKatanaCharacterBase::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AKatanaCharacterBase::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AKatanaCharacterBase::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AKatanaCharacterBase::LookUpAtRate);

	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &AKatanaCharacterBase::StartAttack);
	PlayerInputComponent->BindAction("Attack", IE_Released, this, &AKatanaCharacterBase::StopAttack);

	PlayerInputComponent->BindAction("LockOn", IE_Pressed, this, &AKatanaCharacterBase::TryLockOn);
	PlayerInputComponent->BindAction("Rolling", IE_Pressed, this, &AKatanaCharacterBase::TryRolling);

	PlayerInputComponent->BindAction("LockOnNextTarget", IE_Pressed, this, &AKatanaCharacterBase::TryLockOnNextTarget);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &AKatanaCharacterBase::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AKatanaCharacterBase::TouchStopped);

	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AKatanaCharacterBase::Tick(float DeltaSeconds)
{
	TargetCheck();
}

void AKatanaCharacterBase::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	Jump();
}

void AKatanaCharacterBase::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	StopJumping();
}

void AKatanaCharacterBase::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AKatanaCharacterBase::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}


void AKatanaCharacterBase::PlayerStartJump()
{
	if (CanJump() && bisTryJump)
	{
		Jump();
	}
}



void AKatanaCharacterBase::PlayerStopJump()
{
	if (!CanJump() && !bisTryJump)
	{
		StopJumping();
	}

}

// �� �κ� �ٲ�
void AKatanaCharacterBase::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		if (bisTryMove)
		{
			
			const FRotator Rotation = Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);

			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
			AddMovementInput(Direction, Value);
		}
	}
}


void AKatanaCharacterBase::MoveRight(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		if (bisTryMove)
		{
			const FRotator Rotation = Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);

			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
			AddMovementInput(Direction, Value);
		}

	}
}

void AKatanaCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	//�ִ� ���� ������.
	MaxGuard = GetGuard();

	CurrentSuperArmour();

	if (EquippedWeapon == nullptr && DefaultWeaponMesh && IsValid(SpawnActor) == false)
	{
		FName WeaponSocketName = "R_Hand_Weapon";
		FTransform SocketTransform = GetMesh()->GetSocketTransform(WeaponSocketName, ERelativeTransformSpace::RTS_World);
		SpawnActor = SpawnWeaponActor(DefaultWeaponMesh, SocketTransform, WeaponSocketName);
	}

}

void AKatanaCharacterBase::SetDashDelay()
{
	GetWorldTimerManager().IsTimerActive(DashDelayTimerHandle);

	GetWorldTimerManager().SetTimer(DashDelayTimerHandle,
		FTimerDelegate::CreateLambda([&]()
			{
				ChangePlayerState(EPlayerActionState::NONE);
			}),
		GetMesh()->GetAnimInstance()->Montage_GetPlayRate(HitMontage) - 0.4f, false);
}


//ī�޶� ���� �������� ȸ��
FRotator AKatanaCharacterBase::Direction_Camera_LookingAt()
{
	if (bIsLockOn == true)
	{
		FRotator PlayerRotToCamera = UKismetMathLibrary::FindLookAtRotation(this->GetActorLocation(), LockedOnEnemy->GetActorLocation());
		SetActorRotation(FRotator(0, PlayerRotToCamera.Yaw, 0));

		return PlayerRotToCamera;
	}


	return FRotator::ZeroRotator;
}


// ���� ����
void AKatanaCharacterBase::StartAttack()
{
	bIsattackcount = true;

	if (AttackCountNumber <= 1)
	{
		AttackCountNumber++;
	}

	// �⺻ ���°� �ƴ� ���� ��
	if (Current_Skill_State != EPlayerSkillState::NONE) return;
	if (Current_Player_State != EPlayerActionState::NONE)
	{

		return;
	}
	if (!GetMesh()->GetAnimInstance()->Montage_IsPlaying(RollingMontage)
		&& !GetMesh()->GetAnimInstance()->Montage_IsPlaying(HitMontage)
		&& IsAlive() && bisTryMove)
	{
		ChangePlayerState(EPlayerActionState::ATTACK);

		PlayAnimMontage(BasicAttackAnimation, GetAttackSpeed()); // ���⿡ ����ȭ ��ų ���� ��ȭ ��Ű�� ��.
	}
}


// ���� ��
void AKatanaCharacterBase::StopAttack()
{
	bIsattackcount = false;
	if (Current_Player_State != EPlayerActionState::ATTACK) return;
}



void AKatanaCharacterBase::OnHealthChanged_Implementation(float DeltaHealth, const FGameplayTagContainer& SourceTags)
{
	if (IsAlive() == false)
	{
		ChangePlayerState(EPlayerActionState::DEAD);
	}
}



void AKatanaCharacterBase::OnDamaged_Implementation(float DamageAmount, const FHitResult& HitResult, const FGameplayTagContainer& DamageTags, ACharacterBase* InstigatorCharacter, AActor* DamageCauser)
{
	// ���� �Ƹ� �κ��̴�.
	if (bGuardSuperArmour == true || bSkillSuperArmour == true || bSpecialSkillSuperArmour == true)
	{
		UGameplayStatics::PlaySoundAtLocation(this, SuperArmourHitSound, GetActorLocation());
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, SuperArmourHitEffect, GetActorLocation());
		return;
	}

	if (DamageCauser == nullptr) return;

	FVector attackLocation = GetActorLocation();
	FVector hitLocation = DamageCauser->GetActorLocation();
	FVector hitDirection = (hitLocation - attackLocation).GetSafeNormal();

	// �´� ������ ����� ���� ������ ������ ����
	FVector actorForwardVector = GetActorForwardVector();
	float dotProduct = FVector::DotProduct(hitDirection, actorForwardVector);

	if (dotProduct > 0.0f)
	{
		// ���� ������ ������ ������ ���
		PlayAnimMontage(HitMontage, 1.0f, "Front");
		ChangePlayerState(EPlayerActionState::ROLLING);
		SetDashDelay();
	}
	else
	{
		// ���� ������ ������ �Ĺ��� ���
		PlayAnimMontage(HitMontage, 1.0f, "Back");
		ChangePlayerState(EPlayerActionState::ROLLING);
		SetDashDelay();

	}
}

void AKatanaCharacterBase::OnGuardChanged_Implementation(float DeltaGuard, const FGameplayTagContainer& SourceTags)
{
	CurrentSuperArmour();
}

void AKatanaCharacterBase::CurrentSuperArmour()
{
	// ���� ������ ���� ���۾Ƹ�.
	bGuardSuperArmour = (GetGuard() <= 0.0f) ? false : true;
}



void AKatanaCharacterBase::PlaySuperArmourSkillState()
{
	ChangeSkillState(EPlayerSkillState::SUPER_ARMOUR);
}

void AKatanaCharacterBase::PlayNoneSuperArmourSkillState()
{
	ChangeSkillState(EPlayerSkillState::NONE_SUPER_ARMOUR);
}

void AKatanaCharacterBase::StopSkillState()
{
	ChangeSkillState(EPlayerSkillState::NONE);
}


void AKatanaCharacterBase::StopAttackState()
{
	ChangePlayerState(EPlayerActionState::NONE);
}


void AKatanaCharacterBase::TryRolling_Implementation()
{
	if (bisRolling == false) return;

	if (GetCharacterMovement()->IsFalling())
	{
		return;
	}

	if (GetMesh()->GetAnimInstance()->Montage_IsPlaying(HitMontage) ||
		GetMesh()->GetAnimInstance()->Montage_IsPlaying(RollingMontage))
	{
		return;
	}

	const FVector InputVector = GetInputVector();

	ChangePlayerState(EPlayerActionState::ROLLING);

	if (!InputVector.IsZero())
	{
		const FRotator Rotation = InputVector.Rotation();
		SetActorRotation(Rotation);
	}

	PlayAnimMontage(RollingMontage, 1.0f);


}

// ���� ���߿� Ű����� �ӷ��� �������� �ٲ��ִ� �Լ�..
FVector AKatanaCharacterBase::GetInputVector()
{
	FVector InputVector = FVector::ZeroVector;

	if (Controller != nullptr)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const float ForwardValue = InputComponent->GetAxisValue("MoveForward");
		const float RightValue = InputComponent->GetAxisValue("MoveRight");
		InputVector = (ForwardValue * FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X))
			+ (RightValue * FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y));
		InputVector.Z = 0.0f;
		InputVector.Normalize();
	}

	return InputVector;
}

//�Ͽ��� ������ �����ϰ� �Ͽ��� ���� ������ Ȱ��ȭ�˻�
void AKatanaCharacterBase::TryLockOn_Implementation()
{
	if (bIsLockOn)
	{
		// �Ͽ��� �̹� ���������� ���� Ÿ�� ����
		bIsLockOn = false;
		LockedOnEnemy = nullptr;
	}
	else
	{
		// �Ͽ��� ���������� �Ѱ� Ÿ�� ã��
		LockedOnEnemy = FindTargetEnemy();
		bIsLockOn = (LockedOnEnemy != nullptr);
	}
}

void AKatanaCharacterBase::TryLockOnNextTarget_Implementation()
{
	if (bIsLockOn == true)
	{
		// �Ͽ��� �������� ���� ���� Ÿ�� ã�� ����
		AActor* NewLockedOnEnemy = FindNextClosestEnemy();

		if (NewLockedOnEnemy)
		{
			// ���� �Ͽ��� ���� ���ο� ������ ��ü
			LockedOnEnemy = NewLockedOnEnemy;
		}
	}
}

AActor* AKatanaCharacterBase::FindTargetEnemy()
{
	if (bIsLockOn == true) return LockedOnEnemy;

	// ������ �õ��� �� �����ؾ� �ϴ� ���� ����� ����
	TArray<AActor*> ActorsIgnore;
	ActorsIgnore.Add(this);

	// ������ �˻��� �浹 ����� ������ �迭
	TArray<FHitResult> HitArray;

	// �˻��� �浹 ������Ʈ Ÿ���� ����
	TArray<TEnumAsByte<EObjectTypeQuery>> objectType;
	objectType.Emplace(UEngineTypes::ConvertToObjectType(ECC_Pawn));

	// SphereTraceMultiForObjects �Լ��� ����Ͽ� ���� ����� �˻�
	bool bHit = UKismetSystemLibrary::SphereTraceMultiForObjects(GetWorld(),
		GetActorLocation(), GetActorLocation(),
		LockOnRange, objectType,
		false, ActorsIgnore, EDrawDebugTrace::None,
		HitArray, true);



	if (!bHit)
	{
		return nullptr;
	}

	float MinDistance = FLT_MAX;
	ACharacterBase* ClosestEnemy = nullptr;

	for (const auto& Hit : HitArray)
	{
		ACharacterBase* HitCharacter = Cast<ACharacterBase>(Hit.GetActor());

		if (HitCharacter && IsEnemyInFront(HitCharacter) && !IsWallBetween(Hit))
		{
			if (!HitCharacter->IsAlive())
			{
				continue;
			}

			float Distance = FVector::Dist(HitCharacter->GetActorLocation(), GetActorLocation());

			if (Distance < MinDistance)
			{
				MinDistance = Distance;
				ClosestEnemy = HitCharacter;
			}
		}
	}

	LockedOnEnemy = ClosestEnemy;

	return LockedOnEnemy;
}

AActor* AKatanaCharacterBase::FindNextClosestEnemy()
{
	// ���� �Ͽµ� ���� �����ϰ� ���� ����� �ٸ� ���� ã��
	TArray<AActor*> ActorsToIgnore = { this, LockedOnEnemy };
	TArray<FHitResult> HitResults;

	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Emplace(UEngineTypes::ConvertToObjectType(ECC_Pawn));

	bool bHit = UKismetSystemLibrary::SphereTraceMultiForObjects(
		GetWorld(),
		GetActorLocation(),
		GetActorLocation(),
		LockOnRange,
		ObjectTypes,
		false,
		ActorsToIgnore,
		EDrawDebugTrace::None,
		HitResults,
		true
	);

	if (!bHit)
	{
		return nullptr;
	}

	float MinDistanceSquared = MAX_FLT;
	ACharacterBase* NextClosestEnemy = nullptr;

	for (const FHitResult& Hit : HitResults)
	{
		ACharacterBase* HitCharacter = Cast<ACharacterBase>(Hit.GetActor());

		if (HitCharacter && IsEnemyInFront(HitCharacter) && !IsWallBetween(Hit))
		{
			if (!HitCharacter->IsAlive())
			{
				continue;
			}

			float DistanceSquared = FVector::DistSquared(HitCharacter->GetActorLocation(), GetActorLocation());

			if (DistanceSquared < MinDistanceSquared)
			{
				MinDistanceSquared = DistanceSquared;
				NextClosestEnemy = HitCharacter;
			}
		}
	}

	return NextClosestEnemy;
}


// ī�޶� ȸ��
void AKatanaCharacterBase::DieCameraMove_Implementation()
{

}


// ������ ������ ����
void AKatanaCharacterBase::ReturnToVillage()
{
	// ������ �̵��ϴ� �ڵ�
	FString levelName = "tawn"; // ���� �� �̸�
	UGameplayStatics::OpenLevel(GetWorld(), FName(*levelName));
}

void AKatanaCharacterBase::DieAction()
{
	APlayerCharacterBase::DieAction();
}

// �÷��̾� ���� ��ȭ
void AKatanaCharacterBase::ChangePlayerState(EPlayerActionState ChangeState)
{
	if (Current_Player_State == ChangeState || Current_Player_State == EPlayerActionState::DEAD) return;

	// Exit
	switch (Current_Player_State)
	{
	case EPlayerActionState::NONE:
		AttackCountNumber = 0;
		break;
	case EPlayerActionState::ATTACK:
		bisTryMove = true;
		bIsAttack = true;
		break;
	case EPlayerActionState::ROLLING:
		bisTryMove = true;
		bisTryJump = true;
		break;
	case EPlayerActionState::SKILLATTACK:
		bisTryMove = true;
		bIsAttack = true;
		bisTryJump = true;
		bisRolling = true;
		break;
	case EPlayerActionState::SUPER_ARMOUR:
		bisTryMove = true;
		bIsAttack = true;
		bisRolling = true;
		bSkillSuperArmour = false;
		break;
	case EPlayerActionState::NONE_SUPER_ARMOUR:
		bisTryMove = true;
		bIsAttack = true;
		bisRolling = true;
		break;
	case EPlayerActionState::DEAD:
		break;
	default:
		break;
	}

	//Enter
	switch (ChangeState)
	{
	case EPlayerActionState::NONE:
		AttackCountNumber = 0;
		break;
	case EPlayerActionState::ATTACK:
		bisTryMove = false;
		bIsAttack = false;
		break;
	case EPlayerActionState::ROLLING:
		bisTryMove = false;
		bisTryJump = false;
		break;
	case EPlayerActionState::SKILLATTACK:
		bisTryMove = false;
		bIsAttack = false;
		bisTryJump = false;
		bisRolling = false;
		break;
	case EPlayerActionState::SUPER_ARMOUR:
		bisTryMove = false;
		bIsAttack = false;
		bisRolling = false;
		bSkillSuperArmour = true;
		break;
	case EPlayerActionState::NONE_SUPER_ARMOUR:
		bisTryMove = false;
		bIsAttack = false;
		bisRolling = false;
		break;
	case EPlayerActionState::DEAD:
		bisTryMove = false;
		bIsAttack = false;
		bisTryJump = false;
		bisRolling = false;
		HandleDie();

		break;
	default:
		break;
	}

	Current_Player_State = ChangeState;
}


// �̰� ��ų ������Ʈ������ �ϰ� ����. �׷��� �� ���۾Ƹ�, ���۾Ƹ� ��ų ������Ʈ�� ����
// ���� ��ų ������Ʈ ���̶�� �����ϰ� �ƴ϶��
void AKatanaCharacterBase::ChangeSkillState(EPlayerSkillState ChangeState)
{
	if (Current_Skill_State == ChangeState || Current_Skill_State == EPlayerSkillState::DEAD) return;

	switch (Current_Skill_State)
	{
	case EPlayerSkillState::NONE:
		break;
	case EPlayerSkillState::SUPER_ARMOUR:
		bisTryMove = true;
		bIsAttack = true;
		bisTryJump = true;
		bSkillSuperArmour = false;
		break;
	case EPlayerSkillState::NONE_SUPER_ARMOUR:
		bisTryMove = true;
		bIsAttack = true;
		bisTryJump = true;
		break;
	case EPlayerSkillState::DEAD:
		break;
	default:
		break;
	}

	switch (ChangeState)
	{
	case EPlayerSkillState::NONE:
		break;
	case EPlayerSkillState::SUPER_ARMOUR:
		bisTryMove = false;
		bIsAttack = false;
		bisTryJump = false;
		bSkillSuperArmour = true;
		break;
	case EPlayerSkillState::NONE_SUPER_ARMOUR:
		bisTryMove = false;
		bIsAttack = false;
		bisTryJump = false;
		break;
	case EPlayerSkillState::DEAD:
		break;
	default:
		break;
	}

	Current_Skill_State = ChangeState;
}



//Ÿ�� äũ�ؼ� �����ϱ�
void AKatanaCharacterBase::TargetCheck()
{
	if (IsValid(LockedOnEnemy) && bIsLockOn == true)
	{
		// LockedOnEnemy->GetActorLocation()���� ������ ���� �����.
		FVector LockAtEnemyPosion = LockedOnEnemy->GetActorLocation() - FVector(0.0f, 0.0f, 50.0f);
		FRotator PlayerRot = UKismetMathLibrary::FindLookAtRotation(this->GetActorLocation(), LockAtEnemyPosion);
		PlayerRot.Roll = 0;
		GetController()->SetControlRotation(PlayerRot);
		if (!bIsAttack && bisRolling)
		{
			SetActorRotation(FRotator(0, PlayerRot.Yaw, 0));
		}
	}
}

// ��� ��ü
void AKatanaCharacterBase::UnEquipWeapon()
{
	APlayerCharacterBase::UnEquipWeapon();

	if (IsValid(SpawnActor))
	{
		SpawnActor->Destroy();
		//SpawnActor = nullptr;
	}

	FName WeaponSocketName = "R_Hand_Weapon";
	FTransform SocketTransform = GetMesh()->GetSocketTransform(WeaponSocketName, ERelativeTransformSpace::RTS_World);
	SpawnActor = SpawnWeaponActor(DefaultWeaponMesh, SocketTransform, WeaponSocketName);
}

// ��� ����
void AKatanaCharacterBase::EquipWeapon(UItem_WeaponBase* WeaponToEquip)
{
	APlayerCharacterBase::EquipWeapon(WeaponToEquip);

	if (!IsValid(EquippedWeapon) || !IsValid(EquippedWeapon->WeaponMesh)) return;

	if (IsValid(SpawnActor))
	{
		SpawnActor->Destroy();
	}

	FName WeaponSocketName = "R_Hand_Weapon";
	FTransform SocketTransform = GetMesh()->GetSocketTransform(WeaponSocketName, ERelativeTransformSpace::RTS_World);
	SpawnActor = SpawnWeaponActor(EquippedWeapon->WeaponMesh, SocketTransform, WeaponSocketName);
}

// ������ ����.
AEquipSMActor* AKatanaCharacterBase::SpawnWeaponActor(TSubclassOf<class AEquipSMActor> WeaponMesh, const FTransform& SocketTransform, const FName& SocketName)
{
	if (!IsValid(WeaponMesh)) return nullptr;

	AEquipSMActor* NewWeaponActor = GetWorld()->SpawnActor<AEquipSMActor>(WeaponMesh, SocketTransform);

	if (!IsValid(NewWeaponActor)) return nullptr;

	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
	NewWeaponActor->AttachToComponent(GetMesh(), AttachmentRules, SocketName);

	return NewWeaponActor;
}


// ����ȭ
bool AKatanaCharacterBase::CanOverDriveSkill()
{
	// �ִ� ü���� 30%�� ���
	float MaxHealthThreshold = GetMaxHealth() * 0.3f;

	// ���� ü���� �ִ� ü���� 30% �̸��� ��� false�� ��ȯ
	if (GetHealth() < MaxHealthThreshold)
	{
		return false;
	}

	// ��ų�� �ߵ������Ƿ� true�� ��ȯ
	return true;
}



void AKatanaCharacterBase::OnSalamandersBegin()
{
	ElementalAttack = true;
}

void AKatanaCharacterBase::OnSalamandersEnd()
{
	ElementalAttack = false;
}

void AKatanaCharacterBase::OnIceQueenBegin()
{
	ElementalAttack_Icy = true;
}

void AKatanaCharacterBase::OnIceQueenEnd()
{
	ElementalAttack_Icy = false;
}


UNiagaraSystem* AKatanaCharacterBase::OnElementalSlashVFX(UNiagaraSystem* FireSlash, UNiagaraSystem* IceSlash, UNiagaraSystem* FireNIceSlash, UNiagaraSystem* NormalSlash)
{
	if (ElementalAttack == true && ElementalAttack_Icy == true)
	{
		return FireNIceSlash;
	}

	if (ElementalAttack == true) return FireSlash;

	if (ElementalAttack_Icy == true) return IceSlash;

	return NormalSlash;
}


bool AKatanaCharacterBase::IsEnemyInFront(ACharacterBase* Enemy) const
{
	///*ĳ���� �����̴� -> ���Ͱ� ĳ���� �ٷ� �ڿ� �־ �Ͽ� ���Ѵ�.*/
	//	//FVector HitCharacterDirection = (HitCharacter->GetActorLocation() - GetActorLocation()).GetSafeNormal();

	//	/*ī�޶� �����̴� -> ���Ͱ� ĳ���� �ٷ� �ڿ� �־ �Ͽ� �Ѵ�.(ī�޶� �ٷ� �տ����� ����)*/
	//FVector HitCharacterDirection = (HitCharacter->GetActorLocation() - FollowCamera->GetComponentLocation()).GetSafeNormal();

	FVector EnemyDirection = (Enemy->GetActorLocation() - FollowCamera->GetComponentLocation()).GetSafeNormal();
	float DotProduct = FVector::DotProduct(EnemyDirection, FollowCamera->GetForwardVector());
	return DotProduct > 0.36f;
}

bool AKatanaCharacterBase::IsWallBetween(const FHitResult& HitResult) const
{
	FVector Start = GetActorLocation();
	FVector End = HitResult.GetActor()->GetActorLocation();
	FHitResult WallHitResult;

	bool bHitWall = UKismetSystemLibrary::LineTraceSingle(
		GetWorld(),
		Start,
		End,
		UEngineTypes::ConvertToTraceType(ECC_Visibility),
		false,
		TArray<AActor*>(),
		EDrawDebugTrace::None,
		WallHitResult,
		true
	);

	return bHitWall;
}