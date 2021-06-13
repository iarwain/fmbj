/**
 * @file Object.cpp
 * @date 31-May-2021
 */

#include "Object.h"

void Object::SetAnim(const orxSTRING _zAnim)
{
    ScrollObject::SetAnim(_zAnim, orxFALSE, orxTRUE);
}

void Object::OnCreate()
{
    // Init variables
    meInitialOrientation = !orxString_ICompare(orxConfig_GetString("Orientation"), "left") ? OrientationLeft : OrientationRight;
    meOrientation = OrientationNone;

    // Set orientation
    SetOrientation(meInitialOrientation);

    // Update status
    orxConfig_SetBool("IsObject", orxTRUE);
}

void Object::OnDelete()
{
}

void Object::Update(const orxCLOCK_INFO &_rstInfo)
{
}

void Object::SetOrientation(Orientation _eOrientation)
{
    orxASSERT(_eOrientation < OrientationNumber);

    // Calls children callback
    OnNewOrientation(_eOrientation);
}

void Object::OnNewOrientation(Orientation _eOrientation)
{
    // Stores new orientation
    meOrientation = _eOrientation;
}
