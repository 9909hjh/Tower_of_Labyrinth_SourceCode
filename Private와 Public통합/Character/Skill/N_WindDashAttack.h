

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "../KatanaCharacterBase.h"

#include "N_WindDashAttack.generated.h"


/**
 * 작성자 : 20181289 한주형
 * 질풍참에 대한 어택 애님 노티파이이다.
 */
UCLASS()
class GRADUATEPROJECT_API UN_WindDashAttack : public UAnimNotify
{
	GENERATED_BODY()

	UN_WindDashAttack(const FObjectInitializer& ObjectInitializer);

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

private:
	// 공격의 피해량입니다.
	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack Properties", meta = (AllowPrivateAccess = "true"))
		float DamageAmount;*/

	// 공격 범위입니다.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack Properties", meta = (AllowPrivateAccess = "true"))
		FVector AttackBoundingBoxExtents;

	// 활성화한 경우, 보는 방향으로 회전시킵니다. 비활성화한 경우, AttackBoundingBoxRelativeRotation 값을 따릅니다.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack Properties", meta = (AllowPrivateAccess = "true"))
		bool bUseControllerRotation;

	// 공격 위치입니다. 캐릭터에 상대적입니다. bUseControllerRotation 이 활성화된 경우, 보는 방향에 상대적입니다.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack Properties", meta = (AllowPrivateAccess = "true"))
		FVector AttackBoundingBoxRelativePosition;

	// 공격 회전값입니다. 캐릭터에 상대적입니다.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack Properties", meta = (AllowPrivateAccess = "true", EditCondition = "bUseControllerRotation == false"))
		FRotator AttackBoundingBoxRelativeRotation;

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack Properties|Debug", meta = (AllowPrivateAccess = "true"))
		bool bDrawDebug;*/

	// 적에게 적중한 경우 재생될 사운드입니다.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack Properties|Sound", meta = (AllowPrivateAccess = "true"))
		class USoundBase* Sound_WhenHit;

	UPROPERTY(Transient)
	AKatanaCharacterBase* KatanaCharacter;
};
