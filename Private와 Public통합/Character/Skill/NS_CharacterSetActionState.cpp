
#include "Character/Skill/NS_CharacterSetActionState.h"


UNS_CharacterSetActionState::UNS_CharacterSetActionState(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer),
CharaterActionState(EPlayerActionState::SKILLATTACK)
{

}

void UNS_CharacterSetActionState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	if (AKatanaCharacterBase* KatanaCharacter = Cast<AKatanaCharacterBase>(MeshComp->GetOwner()))
	{
		if (CharaterActionState != EPlayerActionState::NONE)
		{
			KatanaCharacter->ChangePlayerState(CharaterActionState);
		}
	}
}

void UNS_CharacterSetActionState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	if (!GWorld->HasBegunPlay()) return;

	if (AKatanaCharacterBase* KatanaCharacter = Cast<AKatanaCharacterBase>(MeshComp->GetOwner()))
	{
		if (CharaterActionState != EPlayerActionState::NONE)
		{
			KatanaCharacter->ChangePlayerState(EPlayerActionState::NONE);
		}
	}
}
