
#include "Character/Skill/NS_SetPlayerCollision.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"

UNS_SetPlayerCollision::UNS_SetPlayerCollision(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer),
ChangeCollision(TEXT("IgnoreOnlyPawn")),
DefaultCollision(TEXT("Pawn"))
{
}

void UNS_SetPlayerCollision::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	if (!MeshComp || !MeshComp->GetOwner())
	{
		return;
	}

	if (AKatanaCharacterBase* KatanaCharacter = Cast<AKatanaCharacterBase>(MeshComp->GetOwner()))
	{
		UCapsuleComponent* CapsuleComponent = KatanaCharacter->GetCapsuleComponent();
		if (!CapsuleComponent)
		{
			return;
		}

		if (CapsuleComponent->GetCollisionProfileName() != FName(ChangeCollision))
		{
			CapsuleComponent->SetCollisionProfileName(ChangeCollision, true);
		}
	}
}


void UNS_SetPlayerCollision::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	if (!GWorld->HasBegunPlay()) return;


	if (AKatanaCharacterBase* KatanaCharacter = Cast<AKatanaCharacterBase>(MeshComp->GetOwner()))
	{
		UCapsuleComponent* CapsuleComponent = KatanaCharacter->GetCapsuleComponent();
		if (!CapsuleComponent)
		{
			return;
		}

		if (CapsuleComponent->GetCollisionProfileName() != FName(DefaultCollision))
		{
			CapsuleComponent->SetCollisionProfileName(DefaultCollision, true);
		}
	}
}
