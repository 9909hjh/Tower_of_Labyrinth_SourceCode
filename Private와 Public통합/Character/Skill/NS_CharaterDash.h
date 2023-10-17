

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "../PlayerState/PlayerActionState.h"
#include "../KatanaCharacterBase.h"

#include "NS_CharaterDash.generated.h"

/**
 * �ۼ��� : 20181289 ������
 * ĳ���Ͱ� ������ ���� �Ÿ��� �̵��ϴ� �ִϸ��̼� ��Ƽ���� ������Ʈ
 */
UCLASS()
class GRADUATEPROJECT_API UNS_CharaterDash : public UAnimNotifyState
{
	GENERATED_BODY()

	UNS_CharaterDash(const FObjectInitializer& ObjectInitializer);

	virtual void NotifyBegin(class USkeletalMeshComponent* MeshComp, class UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;

	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) override;

	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

private:
	//UPROPERTY(Transient)
	//class AKatanaCharacterBase* KatanaCharacter;

	float CurrentElapsedTime;

	float TotalTime;

	FVector CurrentLocation;

	FVector TargetLocation;

	FRotator FixedRotation;

	// Ȱ��ȭ�� ���, ���� �������� �̵��ϰ�, ��Ȱ��ȭ�� ���, ĳ���� �� �������� �̵��մϴ�.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool bUseControllerRotation;

	// �뽬�� �����Դϴ�.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float DashLength;

	// �߷��Դϴ�. ���߿��� ����� ��� �߷��� ����޽��ϴ�.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float DashGravity;

	// Ease In Ʈ������ ��� �����Դϴ�.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool bEaseIn;

	// Ease Out Ʈ������ ��� �����Դϴ�.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool bEaseOut;

	// ���ӽð����� ������ ActionState�� ����˴ϴ�. NONE�� ��� ������ �õ����� �ʽ��ϴ�.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EPlayerActionState CharaterActionState;

};
