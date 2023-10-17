

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "../PlayerState/PlayerActionState.h"
#include "../KatanaCharacterBase.h"

#include "NS_CharacterSetActionState.generated.h"

/**
 * �ۼ��� : 20181289 ������
 * ĳ������ ���¸� �ٲٴ� ��Ƽ���� ������Ʈ�Դϴ�.
 */
UCLASS()
class GRADUATEPROJECT_API UNS_CharacterSetActionState : public UAnimNotifyState
{
	GENERATED_BODY()

	UNS_CharacterSetActionState(const FObjectInitializer& ObjectInitializer);

	virtual void NotifyBegin(class USkeletalMeshComponent* MeshComp, class UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;

	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

private:
	//UPROPERTY(Transient)
	//class AKatanaCharacterBase* KatanaCharacter;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EPlayerActionState CharaterActionState;
};
