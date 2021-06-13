/**
 * @file Object.h
 * @date 31-May-2021
 */

#ifndef __OBJECT_H__
#define __OBJECT_H__

#include "fmbj.h"

/** Object Class
 */
class Object : public ScrollObject
{
public:

    enum Orientation
    {
        OrientationLeft = 0,
        OrientationRight,

        OrientationNumber,

        OrientationNone = orxENUM_NONE
    };


                void            SetOrientation(Orientation _eOrientation);

                Orientation     GetOrientation() const                          {return meOrientation;}
                Orientation     GetInitialOrientation() const                   {return meInitialOrientation;}

                void            SetAnim(const orxSTRING _zAnim);


protected:

                void            OnCreate();
                void            OnDelete();
                void            Update(const orxCLOCK_INFO &_rstInfo);

    virtual     void            OnNewOrientation(Orientation _eOrientation);


private:

                Orientation     meInitialOrientation;
                Orientation     meOrientation;
};

#endif // __OBJECT_H__
