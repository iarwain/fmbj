/**
 * @file Player.cpp
 * @date 4-Apr-2021
 */

#include "Player.h"

void Player::OnCreate()
{
    // Call parent method
    Character::OnCreate();

    // Enable its physical inputs
    const orxSTRING zSet = orxInput_GetCurrentSet();
    orxInput_SelectSet(orxConfig_GetString("Input"));
    orxInput_SetTypeFlags(orxINPUT_KU32_MASK_TYPE_ALL, orxINPUT_KU32_FLAG_TYPE_NONE);
    orxInput_SelectSet(zSet);

    // Update status
    orxConfig_SetBool("IsPlayer", orxTRUE);
}

void Player::OnDelete()
{
}

void Player::Update(const orxCLOCK_INFO &_rstInfo)
{
    // Call parent method
    Character::Update(_rstInfo);
}
