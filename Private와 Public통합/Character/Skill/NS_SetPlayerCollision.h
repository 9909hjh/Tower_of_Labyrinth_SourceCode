

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "../KatanaCharacterBase.h"

#include "NS_SetPlayerCollision.generated.h"

/**
 * @brief �ۼ��� : 20181289 ������
 * �÷��̾��� ��ǳ�� ��ų�� �� �ִ� ������Ʈ �Դϴ�.
 * �÷��̾��� �ݸ����� �ٲٴ� ����� �մϴ�.
 */
UCLASS()
class GRADUATEPROJECT_API UNS_SetPlayerCollision : public UAnimNotifyState
{
	GENERATED_BODY()

	UNS_SetPlayerCollision(const FObjectInitializer& ObjectInitializer);

	virtual void NotifyBegin(class USkeletalMeshComponent* MeshComp, class UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;

	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

private:
	//UPROPERTY(Transient)
	//class AKatanaCharacterBase* KatanaCharacter;

	// @brief �ٲٴ� �ݸ��� �̸�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FName ChangeCollision;

	// @brief �⺻ �ݸ��� �̸�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FName DefaultCollision;

};
