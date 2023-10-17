

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "../PlayerState/PlayerActionState.h"
#include "../KatanaCharacterBase.h"

#include "NS_CharaterDash.generated.h"

/**
 * 작성자 : 20181289 한주형
 * 캐릭터가 앞으로 일정 거리를 이동하는 애니메이션 노티파이 스테이트
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

	// 활성화한 경우, 보는 방향으로 이동하고, 비활성화한 경우, 캐릭터 앞 방향으로 이동합니다.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool bUseControllerRotation;

	// 대쉬의 길이입니다.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float DashLength;

	// 중력입니다. 공중에서 사용할 경우 중력을 적용받습니다.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float DashGravity;

	// Ease In 트랜지션 사용 여부입니다.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool bEaseIn;

	// Ease Out 트랜지션 사용 여부입니다.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool bEaseOut;

	// 지속시간동안 선택한 ActionState로 변경됩니다. NONE인 경우 변경을 시도하지 않습니다.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EPlayerActionState CharaterActionState;

};
