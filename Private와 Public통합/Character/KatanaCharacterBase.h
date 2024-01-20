#pragma once

#include "CoreMinimal.h"
#include "../Player/PlayerCharacterBase.h"
#include "PlayerState/PlayerActionState.h"

#include "Character/Weapon/EquipSMActor.h"
#include "NiagaraComponent.h"
#include "KatanaCharacterBase.generated.h"

UCLASS()
class GRADUATEPROJECT_API AKatanaCharacterBase : public APlayerCharacterBase
{
	GENERATED_BODY()




public:
	AKatanaCharacterBase();

	void BeginPlay() override;

	// �⺻ ����
	void StartAttack();
	void StopAttack();

	void OnHealthChanged_Implementation(float DeltaHealth, const FGameplayTagContainer& SourceTags) override;
	void OnDamaged_Implementation(float DamageAmount, const FHitResult& HitResult, const FGameplayTagContainer& DamageTags, ACharacterBase* InstigatorCharacter, AActor* DamageCauser) override;
	void OnGuardChanged_Implementation(float DeltaGuard, const FGameplayTagContainer& SourceTags) override;

	//�Ѹ� 
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "State|Check")
		void TryRolling();

	// �Ͽ�
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "State|Check")
	void TryLockOn();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "State|Check")
	void TryLockOnNextTarget();

	UFUNCTION(BlueprintCallable, Category = "State|Check")
	AActor* FindTargetEnemy();

	AActor* FindNextClosestEnemy();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "State|Check")
	void DieCameraMove();

	// ������ ���ư���
	void ReturnToVillage();

	void DieAction() override;


	//ĳ���� ����
	void ChangePlayerState(EPlayerActionState ChangeState);
	void ChangeSkillState(EPlayerSkillState ChangeState);

	UFUNCTION(BlueprintCallable, Category = "State|Check")
		void TargetCheck();

	// ���� ����
	void PlayerStartJump();
	void PlayerStopJump();

	void SetDashDelay();

	UFUNCTION(BlueprintCallable, Category = "State|Check")
	FRotator Direction_Camera_LookingAt();

	UFUNCTION(BlueprintCallable, Category = "State|Check")
	void OnRollingEnd();

	//�Է� ���� �Լ�
	FVector GetInputVector();

	/* ��� ���� �� ����*/

	// ��� ����
	void UnEquipWeapon() override;

	// ��� ����
	void EquipWeapon(UItem_WeaponBase* WeaponToEquip) override;

	//�ӽ� ���� ����
	AEquipSMActor* SpawnWeaponActor(TSubclassOf<class AEquipSMActor> WeaponMesh, const FTransform& SocketTransform, const FName& SocketName);



	/* ���� �Լ�*/

	// ���۾Ƹ� ���� �Լ�
	void CurrentSuperArmour();

	UFUNCTION(BlueprintCallable, Category = "State|Check")
	void PlaySuperArmourSkillState();

	UFUNCTION(BlueprintCallable, Category = "State|Check")
	void PlayNoneSuperArmourSkillState();

	UFUNCTION(BlueprintCallable, Category = "State|Check")
	void StopSkillState();


	UFUNCTION(BlueprintCallable, Category = "State|Check")
	void StopAttackState();

	/* ���� ���� �Լ�*/

	/* ����ȭ ���� �Լ�*/
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "State|Buff")
	void OnOverDriveBegin();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "State|Buff")
	void OnOverDriveEnd();

	UFUNCTION(BlueprintCallable, Category = "State|Buff")
	bool CanOverDriveSkill();


	/* �Ӽ� ���� �Լ�*/
	UFUNCTION(BlueprintCallable, Category = "State|Buff")
	void OnSalamandersBegin();

	UFUNCTION(BlueprintCallable, Category = "State|Buff")
	void OnSalamandersEnd();

	UFUNCTION(BlueprintCallable, Category = "State|Buff")
	void OnIceQueenBegin();

	UFUNCTION(BlueprintCallable, Category = "State|Buff")
	void OnIceQueenEnd();


	UFUNCTION(BlueprintPure, Category = "State|Buff")
		UNiagaraSystem* OnElementalSlashVFX(UNiagaraSystem* FireSlash, UNiagaraSystem* IceSlash, UNiagaraSystem* FireNIceSlash, UNiagaraSystem* NormalSlash);


	bool IsEnemyInFront(ACharacterBase* Enemy) const;
	bool IsWallBetween(const FHitResult& HitResult) const;


private:


	//���� ���� �� ĳ���� �ӵ�
	UPROPERTY(VisibleAnywhere, Category = "KatanaCharacterBase|AttackState", meta = (AllowPrivateAccess = "true"))
	float PlayAttackWalkSpeed;

	//���� ���� �� ĳ���� �ӵ�
	UPROPERTY(EditAnywhere, Category = "KatanaCharacterBase|AttackState", meta = (AllowPrivateAccess = "true"))
	float StopAttackWalkSpeed;

	// �߽� ����
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "KatanaCharacterBase|AttackState", meta = (AllowPrivateAccess = "true"))
	float MaxGuard;

	// ���� ������ ���� ���۾Ƹ�
	UPROPERTY(VisibleAnywhere, Category = "KatanaCharacterBase|AttackState", meta = (AllowPrivateAccess = "true"))
	bool bGuardSuperArmour;

	// ��ų ���� ���۾Ƹ�
	UPROPERTY(EditAnywhere, Category = "KatanaCharacterBase|AttackState", meta = (AllowPrivateAccess = "true"))
	bool bSkillSuperArmour;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "KatanaCharacterBase|AttackState", meta = (AllowPrivateAccess = "true"))
	bool bSpecialSkillSuperArmour;

	//�⺻ ���� äũ
	UPROPERTY(VisibleAnywhere, Category = "KatanaCharacterBase|AttackState", meta = (AllowPrivateAccess = "true"))
	EPlayerActionState Current_Player_State;

	UPROPERTY(VisibleAnywhere, Category = "KatanaCharacterBase|AttackState", meta = (AllowPrivateAccess = "true"))
	EPlayerSkillState Current_Skill_State;

	// true�� �̵� ����
	UPROPERTY(VisibleAnywhere, Category = "KatanaCharacterBase|AttackState", meta = (AllowPrivateAccess = "true"))
	bool bisTryMove;

	// true�� ���� ����
	UPROPERTY(VisibleAnywhere, Category = "KatanaCharacterBase|AttackState", meta = (AllowPrivateAccess = "true"))
	bool bIsAttack; // false

		// true�� ���� ����
	UPROPERTY(VisibleAnywhere, Category = "KatanaCharacterBase|AttackState", meta = (AllowPrivateAccess = "true"))
	bool bisTryJump;

	// true�� ������ ����
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "KatanaCharacterBase|AttackState", meta = (AllowPrivateAccess = "true"))
	bool bisRolling;

	//�Ͽ� ����
	UPROPERTY(EditAnywhere, Category = "KatanaCharacterBase|LockOn", meta = (AllowPrivateAccess = "true"))
	float LockOnRange;

	// �Ͽ� �ΰ�?
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "KatanaCharacterBase|AttackState", meta = (AllowPrivateAccess = "true"))
	bool bIsLockOn;

	// ���콺 Ȧ�尡 �ƴ� Ŭ���� ���ؼ��� ������ ������ ����� ���� bool��
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "KatanaCharacterBase|AttackState", meta = (AllowPrivateAccess = "true"))
	bool bIsattackcount;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "KatanaCharacterBase|AttackState", meta = (AllowPrivateAccess = "true"))
	int AttackCountNumber;

	/*�ִϸ��̼�*/

	//�⺻ ���� �ִϸ��̼�.
	UPROPERTY(EditAnywhere, Category = "KatanaCharacterBase|Animation", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* BasicAttackAnimation;

	//������ �ִϸ��̼�.
	UPROPERTY(EditAnywhere, Category = "KatanaCharacterBase|Animation", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* RollingMontage;

	//�´� �ִϸ��̼�.
	UPROPERTY(EditAnywhere, Category = "KatanaCharacterBase|Animation", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* HitMontage;

	// Ÿ�� ��
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "KatanaCharacterBase|AttackState", meta = (AllowPrivateAccess = "true"))
	AActor* LockedOnEnemy;


	FTimerHandle DashDelayTimerHandle;
	FTimerHandle TimerHandle_ReturnToVillage;

	/* ���� ���� */

	//class UItem_WeaponBase* EquippedWeapon;
	UPROPERTY()
		UStaticMeshComponent* EquippedWeaponMesh;

	// ������ ����
	UPROPERTY()
	AEquipSMActor* SpawnActor;

	// �⺻ ����
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Item|Weapon|Mesh", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AEquipSMActor> DefaultWeaponMesh;


	/*���� ���� ����*/
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool ElementalAttack;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool ElementalAttack_Icy;


	/*���� ����*/
	UPROPERTY(EditAnywhere, Category = "KatanaCharacterBase|Sound", meta = (AllowPrivateAccess = "true"))
	USoundBase* SuperArmourHitSound;

	/*���̾ư��� ����*/
	UPROPERTY(EditAnywhere, Category = "KatanaCharacterBase|Effect", meta = (AllowPrivateAccess = "true"))
	UNiagaraSystem* SuperArmourHitEffect;


protected:
	virtual void Tick(float DeltaSeconds);

	void MoveForward(float Value);
	void MoveRight(float Value);
	void TurnAtRate(float Rate);
	void LookUpAtRate(float Rate);

	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


private:

	// ī�޶� ������Ʈ
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	//Die Camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* DieCamera;

	bool bIsTargetEnemy = true;
};


