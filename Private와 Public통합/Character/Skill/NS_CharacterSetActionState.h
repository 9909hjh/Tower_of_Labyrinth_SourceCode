

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "../PlayerState/PlayerActionState.h"
#include "../KatanaCharacterBase.h"

#include "NS_CharacterSetActionState.generated.h"

/**
 * 작성자 : 20181289 한주형
 * 캐릭터의 상태를 바꾸는 노티파이 스테이트입니다.
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
