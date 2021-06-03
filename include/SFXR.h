/**
 * @file SFXR.h
 * @date 2-Jun-2021
 */

#ifndef __SFXR_H__
#define __SFXR_H__

#include "fmbj.h"

/** SFXR Class
 */
class SFXR : public ScrollObject
{
public:
                void            FillBuffer(orxSOUND_STREAM_PACKET &_rstPacket);


protected:

                void            OnCreate();
                void            OnDelete();


private:

                struct
                {
#define SFXR_DEFINE(Type, TYPE, Name) orx##TYPE Name;
#include "SFXR.inc"
#undef SFXR_DEFINE
                }               mstParams;
};

#endif // __SFXR_H__
