
#include "Character/Skill/NS_CharaterDash.h"



#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"


UNS_CharaterDash::UNS_CharaterDash(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer),
CurrentElapsedTime(0.0f),
TotalTime(0.0f),
CurrentLocation(FVector::ZeroVector),
TargetLocation(FVector::ZeroVector),
FixedRotation(FRotator::ZeroRotator),
bUseControllerRotation(false),
DashLength(100.0f),
DashGravity(1.0f),
bEaseIn(false),
bEaseOut(false),
CharaterActionState(EPlayerActionState::SKILLATTACK)
{
	//KatanaCharacter = nullptr;
}




void UNS_CharaterDash::NotifyBegin(class USkeletalMeshComponent* MeshComp, class UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	if (AKatanaCharacterBase* KatanaCharacter = Cast<AKatanaCharacterBase>(MeshComp->GetOwner()))
	{
		CurrentElapsedTime = 0.0f;
		TotalTime = TotalDuration;
		CurrentLocation = KatanaCharacter->GetActorLocation();


		if (bUseControllerRotation && KatanaCharacter->GetController() != nullptr)
		{
			TargetLocation = KatanaCharacter->GetActorLocation() +
				KatanaCharacter->GetControlRotation().Vector() * DashLength;

			FixedRotation = FRotator(0.0f, KatanaCharacter->GetControlRotation().Yaw, 0.0f);
		}
		else
		{
			TargetLocation = KatanaCharacter->GetActorLocation() +
				KatanaCharacter->GetActorForwardVector() * DashLength;

			FixedRotation = KatanaCharacter->GetActorRotation();
		}

		if (CharaterActionState != EPlayerActionState::NONE) KatanaCharacter->ChangePlayerState(CharaterActionState);
	}
}


void UNS_CharaterDash::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);

	CurrentElapsedTime += FrameDeltaTime;

	if (CurrentElapsedTime < TotalTime)
	{
		float ElapsedPercent = CurrentElapsedTime / TotalTime;
		float TargetAlpha;

		if (bEaseIn)
		{
			if (bEaseOut)
			{
				TargetAlpha = UKismetMathLibrary::FInterpEaseInOut(0.0f, 1.0f, ElapsedPercent, 2.0f);
			}
			else
			{
				TargetAlpha = UKismetMathLibrary::Lerp(0.0f, 1.0f, ElapsedPercent * ElapsedPercent);
			}
		}
		else
		{
			if (bEaseOut)
			{
				TargetAlpha = UKismetMathLibrary::Lerp(0.0f, 1.0f, FMath::Pow(ElapsedPercent, 0.5f));
			}
			else
			{
				TargetAlpha = UKismetMathLibrary::Lerp(0.0f, 1.0f, ElapsedPercent);
			}
		}

		//if (MeshComp->GetOwner()->GetMovementComponent()->IsFalling())
		//	TargetLocation += FVector::DownVector * 9.8f * DashGravity;

		MeshComp->GetOwner()->SetActorLocation((CurrentElapsedTime >= TotalTime) ?
			TargetLocation : FMath::Lerp(CurrentLocation, TargetLocation, TargetAlpha),
			true);
		MeshComp->GetOwner()->SetActorRotation(FixedRotation);
	}
}



void UNS_CharaterDash::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	if (!GWorld->HasBegunPlay()) return;

	if (AKatanaCharacterBase* KatanaCharacter = Cast<AKatanaCharacterBase>(MeshComp->GetOwner()))
	{
		//if (ActionState != EActionState::NONE) KatanaCharacter->ChangeActionState(EActionState::NONE);
		if (CharaterActionState == EPlayerActionState::ROLLING) KatanaCharacter->SetDashDelay();
	}
}