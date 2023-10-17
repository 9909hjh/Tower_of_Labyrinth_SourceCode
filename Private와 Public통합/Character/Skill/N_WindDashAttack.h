

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "../KatanaCharacterBase.h"

#include "N_WindDashAttack.generated.h"


/**
 * �ۼ��� : 20181289 ������
 * ��ǳ���� ���� ���� �ִ� ��Ƽ�����̴�.
 */
UCLASS()
class GRADUATEPROJECT_API UN_WindDashAttack : public UAnimNotify
{
	GENERATED_BODY()

	UN_WindDashAttack(const FObjectInitializer& ObjectInitializer);

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

private:
	// ������ ���ط��Դϴ�.
	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack Properties", meta = (AllowPrivateAccess = "true"))
		float DamageAmount;*/

	// ���� �����Դϴ�.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack Properties", meta = (AllowPrivateAccess = "true"))
		FVector AttackBoundingBoxExtents;

	// Ȱ��ȭ�� ���, ���� �������� ȸ����ŵ�ϴ�. ��Ȱ��ȭ�� ���, AttackBoundingBoxRelativeRotation ���� �����ϴ�.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack Properties", meta = (AllowPrivateAccess = "true"))
		bool bUseControllerRotation;

	// ���� ��ġ�Դϴ�. ĳ���Ϳ� ������Դϴ�. bUseControllerRotation �� Ȱ��ȭ�� ���, ���� ���⿡ ������Դϴ�.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack Properties", meta = (AllowPrivateAccess = "true"))
		FVector AttackBoundingBoxRelativePosition;

	// ���� ȸ�����Դϴ�. ĳ���Ϳ� ������Դϴ�.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack Properties", meta = (AllowPrivateAccess = "true", EditCondition = "bUseControllerRotation == false"))
		FRotator AttackBoundingBoxRelativeRotation;

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack Properties|Debug", meta = (AllowPrivateAccess = "true"))
		bool bDrawDebug;*/

	// ������ ������ ��� ����� �����Դϴ�.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack Properties|Sound", meta = (AllowPrivateAccess = "true"))
		class USoundBase* Sound_WhenHit;

	UPROPERTY(Transient)
	AKatanaCharacterBase* KatanaCharacter;
};
