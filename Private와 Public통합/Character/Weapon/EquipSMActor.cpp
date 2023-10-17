


#include "Character/Weapon/EquipSMActor.h"

// Sets default values
AEquipSMActor::AEquipSMActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// DefaultSceneRoot 积己
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = DefaultSceneRoot;

	// Scene Component 积己
	WeaponPivot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	WeaponPivot->SetupAttachment(DefaultSceneRoot);
	WeaponPivot->SetMobility(EComponentMobility::Movable); // 眠啊

	// Static Mesh Component 积己
	EquipWeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	EquipWeaponMesh->SetupAttachment(WeaponPivot);
	EquipWeaponMesh->SetMobility(EComponentMobility::Movable); // 眠啊

}


