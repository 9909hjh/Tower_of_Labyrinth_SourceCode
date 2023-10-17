

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "../KatanaCharacterBase.h"

#include "NS_SetPlayerCollision.generated.h"

/**
 * @brief 작성자 : 20181289 한주형
 * 플레이어의 질풍참 스킬에 들어갈 애님 스테이트 입니다.
 * 플레이어의 콜리전을 바꾸는 기능을 합니다.
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

	// @brief 바꾸는 콜리전 이름
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FName ChangeCollision;

	// @brief 기본 콜리전 이름
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FName DefaultCollision;

};
