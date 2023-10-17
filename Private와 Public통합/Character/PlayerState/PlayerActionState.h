

#pragma once

#include "CoreMinimal.h"

/**
 * �ۼ��� : 20181289 ������
 * ĳ���� ���¸� ��Ƴ��� ������ Ŭ����
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