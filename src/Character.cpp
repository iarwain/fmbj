/**
 * @file Character.cpp
 * @date 4-Apr-2021
 */

#include "Character.h"

void Character::OnCreate()
{
    // Call parent method
    Object::OnCreate();

    // Enable its inputs
    const orxSTRING zSet = orxInput_GetCurrentSet();
    zInputSet = orxConfig_GetString("Input");
    orxInput_SelectSet(zInputSet);
    orxInput_EnableSet(orxInput_GetCurrentSet(), orxTRUE);
    orxInput_SetTypeFlags(orxINPUT_KU32_FLAG_TYPE_NONE, orxINPUT_KU32_MASK_TYPE_ALL);
    orxInput_SelectSet(zSet);

    // Update status
    orxConfig_SetBool("IsCharacter", orxTRUE);

    // Inits vars
    orxConfig_SetBool("IsDead", orxFALSE);
    orxConfig_SetBool("IsDashing", orxFALSE);
    orxConfig_SetBool("IsDashQueued", orxFALSE);
}

void Character::OnDelete()
{
    // Removes its inputs
    orxInput_RemoveSet(zInputSet);

    // Call parent method
    Object::OnDelete();
}

void Character::Update(const orxCLOCK_INFO &_rstInfo)
{
    // Call parent method
    Object::Update(_rstInfo);

    // Not dead?
    if(!orxConfig_GetBool("IsDead"))
    {
        // Push config section
        PushConfigSection();

        // Select input set
        const orxSTRING zSet = orxInput_GetCurrentSet();
        orxInput_SelectSet(orxConfig_GetString("Input"));

        // Not dashing?
        if(!orxConfig_GetBool("IsDashing"))
        {
            // Gets move vector
            orxVECTOR vMove = {orxInput_GetValue("Right") - orxInput_GetValue("Left"), orxFLOAT_0, orxFLOAT_0};
            orxVector_FromCartesianToSpherical(&vMove, &vMove);
            vMove.fRho = orxMIN(vMove.fRho, orxFLOAT_1);

            // Should move?
            if(vMove.fRho != orxFLOAT_0)
            {
                // Update orientation
                if(orxMath_Abs(vMove.fTheta) > orxMATH_KF_PI_BY_2 + orx2F(0.1f))
                {
                    SetOrientation(OrientationLeft);
                }
                else if(orxMath_Abs(vMove.fTheta) < orxMATH_KF_PI_BY_2 - orx2F(0.1f))
                {
                    SetOrientation(OrientationRight);
                }

                // Update anim
                if(orxMath_Abs(vMove.fTheta) >= (orxMATH_KF_PI_BY_2 + orxMATH_KF_PI_BY_4))
                {
                    SetAnim("MoveLeft");
                }
                else if(orxMath_Abs(vMove.fTheta) <= orxMATH_KF_PI_BY_4)
                {
                    SetAnim("MoveRight");
                }
            }
            else
            {
                // Update anim
                SetAnim((GetOrientation() == OrientationLeft) ? "IdleLeft" : "IdleRight");
            }

            // Dash
            if(orxConfig_GetBool("IsDashQueued") || orxInput_HasBeenActivated("Dash"))
            {
                if(vMove.fRho != orxFLOAT_0)
                {
                    vMove.fRho = orxConfig_GetFloat("DashSpeed");
                    SetAnim((GetOrientation() == OrientationLeft) ? "DashLeft" : "DashRight");
                    orxConfig_SetVector("DashVector", &vMove);
                    AddConditionalTrack("Dash");
                }
                orxConfig_SetBool("IsDashQueued", orxFALSE);
            }
            else
            {
                vMove.fRho *= orxConfig_GetFloat("Speed");
            }

            // Update speed
            SetSpeed(*orxVector_FromSphericalToCartesian(&vMove, &vMove));
        }
        else
        {
            // Dash?
            if(orxInput_HasBeenActivated("Dash"))
            {
                // Queue dash
                orxConfig_SetBool("IsDashQueued", orxTRUE);
            }
        }

        // Deselect input set
        orxInput_SelectSet(zSet);

        // Pop config section
        PopConfigSection();
    }
}
