
#include "Character/Skill/N_WindDashAttack.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"


UN_WindDashAttack::UN_WindDashAttack(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer),
	AttackBoundingBoxExtents(100.0f * FVector::OneVector),
	AttackBoundingBoxRelativePosition(FVector::ZeroVector),
	AttackBoundingBoxRelativeRotation(FRotator::ZeroRotator),
	KatanaCharacter(nullptr)
{

}

void UN_WindDashAttack::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	/*KatanaCharacter = Cast<AKatanaCharacterBase>(MeshComp->GetOwner());

	FVector BoxLocation;
	FRotator BoxRotation;

	const FRotator& AttackRelativeRotation = bUseControllerRotation ? FRotator::ZeroRotator : AttackBoundingBoxRelativeRotation;

	if (bUseControllerRotation)
	{
		BoxLocation = KatanaCharacter->GetActorLocation() + KatanaCharacter->GetControlRotation().RotateVector(AttackBoundingBoxRelativePosition);
		BoxRotation = KatanaCharacter->GetControlRotation();
	}
	else
	{
		BoxLocation = KatanaCharacter->GetActorLocation() + KatanaCharacter->GetActorRotation().RotateVector(AttackBoundingBoxRelativePosition);
		BoxRotation = KatanaCharacter->GetActorRotation() + AttackRelativeRotation;
	}

	const TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes = { UEngineTypes::ConvertToObjectType(ECC_Pawn) };
	const TArray<AActor*> IgnoreActors = { KatanaCharacter };

	TArray<FHitResult> HitResultArray;

	UKismetSystemLibrary::BoxTraceMultiForObjects(MeshComp->GetWorld(), BoxLocation, BoxLocation,
		0.5f * AttackBoundingBoxExtents,
		BoxRotation,
		ObjectTypes, false, IgnoreActors,
		bDrawDebug ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None, HitResultArray,
		true, FLinearColor::Red, FLinearColor::Green, 3.0f);*/


}
