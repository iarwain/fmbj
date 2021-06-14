/**
 * @file Character.h
 * @date 4-Apr-2021
 */

#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "Object.h"

/** Character Class
 */
class Character : public Object
{
public:


protected:

                void            OnCreate();
                void            OnDelete();
                void            Update(const orxCLOCK_INFO &Info);

                const orxSTRING zInputSet;


private:
};

#endif // __CHARACTER_H__
