


#include "Character/Weapon/EquipSMActor.h"

// Sets default values
AEquipSMActor::AEquipSMActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// DefaultSceneRoot ����
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = DefaultSceneRoot;

	// Scene Component ����
	WeaponPivot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	WeaponPivot->SetupAttachment(DefaultSceneRoot);
	WeaponPivot->SetMobility(EComponentMobility::Movable); // �߰�

	// Static Mesh Component ����
	EquipWeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	EquipWeaponMesh->SetupAttachment(WeaponPivot);
	EquipWeaponMesh->SetMobility(EComponentMobility::Movable); // �߰�

}


