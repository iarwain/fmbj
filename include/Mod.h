/**
 * @file Mod.h
 * @date 1-Jun-2021
 */

#ifndef __MOD_H__
#define __MOD_H__

#include "fmbj.h"

#include "ksnd.h"

/** Mod Class
 */
class Mod : public ScrollObject
{
public:


protected:

                void            OnCreate();
                void            OnDelete();
                void            Update(const orxCLOCK_INFO &_rstInfo);


private:

                void            UpdateMod();

                KPlayer        *mpstPlayer;
                KSong          *mpstSong;
};

#endif // __MOD_H__
