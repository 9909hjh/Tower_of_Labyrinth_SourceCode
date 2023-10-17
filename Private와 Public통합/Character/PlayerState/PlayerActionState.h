

#pragma once

#include "CoreMinimal.h"

/**
 * 작성자 : 20181289 한주형
 * 캐릭터 상태를 모아놓은 열거형 클래스
 */
UENUM(BlueprintType)
enum class EPlayerActionState : uint8
{
	NONE, ATTACK, ROLLING, SKILLATTACK, SUPER_ARMOUR, NONE_SUPER_ARMOUR, DEAD
};

UENUM(BlueprintType)
enum class EPlayerSkillState : uint8
{
	NONE, SUPER_ARMOUR, NONE_SUPER_ARMOUR, DEAD
};