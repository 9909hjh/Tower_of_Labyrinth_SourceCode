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

	// 기본 공격
	void StartAttack();
	void StopAttack();

	void OnHealthChanged_Implementation(float DeltaHealth, const FGameplayTagContainer& SourceTags) override;
	void OnDamaged_Implementation(float DamageAmount, const FHitResult& HitResult, const FGameplayTagContainer& DamageTags, ACharacterBase* InstigatorCharacter, AActor* DamageCauser) override;
	void OnGuardChanged_Implementation(float DeltaGuard, const FGameplayTagContainer& SourceTags) override;

	//롤링 
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "State|Check")
		void TryRolling();

	// 록온
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "State|Check")
	void TryLockOn();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "State|Check")
	void TryLockOnNextTarget();

	UFUNCTION(BlueprintCallable, Category = "State|Check")
	AActor* FindTargetEnemy();

	AActor* FindNextClosestEnemy();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "State|Check")
	void DieCameraMove();

	// 마을로 돌아가기
	void ReturnToVillage();

	void DieAction() override;


	//캐릭터 상태
	void ChangePlayerState(EPlayerActionState ChangeState);
	void ChangeSkillState(EPlayerSkillState ChangeState);

	UFUNCTION(BlueprintCallable, Category = "State|Check")
		void TargetCheck();

	// 점프 관련
	void PlayerStartJump();
	void PlayerStopJump();

	void SetDashDelay();

	UFUNCTION(BlueprintCallable, Category = "State|Check")
	FRotator Direction_Camera_LookingAt();

	UFUNCTION(BlueprintCallable, Category = "State|Check")
	void OnRollingEnd();

	//입력 방향 함수
	FVector GetInputVector();

	/* 장비 장착 및 스폰*/

	// 장비 해제
	void UnEquipWeapon() override;

	// 장비 장착
	void EquipWeapon(UItem_WeaponBase* WeaponToEquip) override;

	//임시 무기 액터
	AEquipSMActor* SpawnWeaponActor(TSubclassOf<class AEquipSMActor> WeaponMesh, const FTransform& SocketTransform, const FName& SocketName);



	/* 상태 함수*/

	// 슈퍼아머 상태 함수
	void CurrentSuperArmour();

	UFUNCTION(BlueprintCallable, Category = "State|Check")
	void PlaySuperArmourSkillState();

	UFUNCTION(BlueprintCallable, Category = "State|Check")
	void PlayNoneSuperArmourSkillState();

	UFUNCTION(BlueprintCallable, Category = "State|Check")
	void StopSkillState();


	UFUNCTION(BlueprintCallable, Category = "State|Check")
	void StopAttackState();

	/* 버프 관련 함수*/

	/* 광폭화 관련 함수*/
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "State|Buff")
	void OnOverDriveBegin();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "State|Buff")
	void OnOverDriveEnd();

	UFUNCTION(BlueprintCallable, Category = "State|Buff")
	bool CanOverDriveSkill();


	/* 속성 관련 함수*/
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


	//공격 시작 시 캐릭터 속도
	UPROPERTY(VisibleAnywhere, Category = "KatanaCharacterBase|AttackState", meta = (AllowPrivateAccess = "true"))
	float PlayAttackWalkSpeed;

	//공격 정지 시 캐릭터 속도
	UPROPERTY(EditAnywhere, Category = "KatanaCharacterBase|AttackState", meta = (AllowPrivateAccess = "true"))
	float StopAttackWalkSpeed;

	// 멕스 가드
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "KatanaCharacterBase|AttackState", meta = (AllowPrivateAccess = "true"))
	float MaxGuard;

	// 가드 게이지 관련 슈퍼아머
	UPROPERTY(VisibleAnywhere, Category = "KatanaCharacterBase|AttackState", meta = (AllowPrivateAccess = "true"))
	bool bGuardSuperArmour;

	// 스킬 관련 슈퍼아머
	UPROPERTY(EditAnywhere, Category = "KatanaCharacterBase|AttackState", meta = (AllowPrivateAccess = "true"))
	bool bSkillSuperArmour;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "KatanaCharacterBase|AttackState", meta = (AllowPrivateAccess = "true"))
	bool bSpecialSkillSuperArmour;

	//기본 상태 채크
	UPROPERTY(VisibleAnywhere, Category = "KatanaCharacterBase|AttackState", meta = (AllowPrivateAccess = "true"))
	EPlayerActionState Current_Player_State;

	UPROPERTY(VisibleAnywhere, Category = "KatanaCharacterBase|AttackState", meta = (AllowPrivateAccess = "true"))
	EPlayerSkillState Current_Skill_State;

	// true면 이동 가능
	UPROPERTY(VisibleAnywhere, Category = "KatanaCharacterBase|AttackState", meta = (AllowPrivateAccess = "true"))
	bool bisTryMove;

	// true면 공격 가능
	UPROPERTY(VisibleAnywhere, Category = "KatanaCharacterBase|AttackState", meta = (AllowPrivateAccess = "true"))
	bool bIsAttack; // false

		// true면 점프 가능
	UPROPERTY(VisibleAnywhere, Category = "KatanaCharacterBase|AttackState", meta = (AllowPrivateAccess = "true"))
	bool bisTryJump;

	// true면 구르기 가능
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "KatanaCharacterBase|AttackState", meta = (AllowPrivateAccess = "true"))
	bool bisRolling;

	//록온 범위
	UPROPERTY(EditAnywhere, Category = "KatanaCharacterBase|LockOn", meta = (AllowPrivateAccess = "true"))
	float LockOnRange;

	// 록온 인가?
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "KatanaCharacterBase|AttackState", meta = (AllowPrivateAccess = "true"))
	bool bIsLockOn;

	// 마우스 홀드가 아닌 클릭을 통해서도 공격이 가능한 기능을 위한 bool값
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "KatanaCharacterBase|AttackState", meta = (AllowPrivateAccess = "true"))
	bool bIsattackcount;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "KatanaCharacterBase|AttackState", meta = (AllowPrivateAccess = "true"))
	int AttackCountNumber;

	/*애니메이션*/

	//기본 공격 애니메이션.
	UPROPERTY(EditAnywhere, Category = "KatanaCharacterBase|Animation", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* BasicAttackAnimation;

	//구르기 애니메이션.
	UPROPERTY(EditAnywhere, Category = "KatanaCharacterBase|Animation", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* RollingMontage;

	//맞는 애니메이션.
	UPROPERTY(EditAnywhere, Category = "KatanaCharacterBase|Animation", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* HitMontage;

	// 타겟 적
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "KatanaCharacterBase|AttackState", meta = (AllowPrivateAccess = "true"))
	AActor* LockedOnEnemy;


	FTimerHandle DashDelayTimerHandle;
	FTimerHandle TimerHandle_ReturnToVillage;

	/* 무기 장착 */

	//class UItem_WeaponBase* EquippedWeapon;
	UPROPERTY()
		UStaticMeshComponent* EquippedWeaponMesh;

	// 스폰된 액터
	UPROPERTY()
	AEquipSMActor* SpawnActor;

	// 기본 무기
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Item|Weapon|Mesh", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AEquipSMActor> DefaultWeaponMesh;


	/*버프 관련 변수*/
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool ElementalAttack;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool ElementalAttack_Icy;


	/*사운드 변수*/
	UPROPERTY(EditAnywhere, Category = "KatanaCharacterBase|Sound", meta = (AllowPrivateAccess = "true"))
	USoundBase* SuperArmourHitSound;

	/*나이아가라 변수*/
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

	// 카메라 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	//Die Camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* DieCamera;

	bool bIsTargetEnemy = true;
};


