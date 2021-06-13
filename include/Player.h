/**
 * @file Player.h
 * @date 4-Apr-2021
 */

#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Character.h"

/** Player Class
 */
class Player : public Character
{
public:


protected:

                void            OnCreate();
                void            OnDelete();
                void            Update(const orxCLOCK_INFO &Info);


private:
};

#endif // __PLAYER_H__
