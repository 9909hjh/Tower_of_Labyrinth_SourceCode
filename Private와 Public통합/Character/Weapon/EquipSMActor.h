

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EquipSMActor.generated.h"

UCLASS()
class GRADUATEPROJECT_API AEquipSMActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEquipSMActor();

	// Scene Component ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	USceneComponent* DefaultSceneRoot;

	// Scene Component ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	USceneComponent* WeaponPivot;

	// Static Mesh Component ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* EquipWeaponMesh;


};
