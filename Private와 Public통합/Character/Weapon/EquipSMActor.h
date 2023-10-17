

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

	// Scene Component 변수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	USceneComponent* DefaultSceneRoot;

	// Scene Component 변수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	USceneComponent* WeaponPivot;

	// Static Mesh Component 변수
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* EquipWeaponMesh;


};
