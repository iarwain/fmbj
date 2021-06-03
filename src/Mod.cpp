/**
 * @file Mod.cpp
 * @date 1-Jun-2021
 */

#include "Mod.h"

void Mod::OnCreate()
{
  const orxSTRING zMod;

  mpstPlayer  = orxNULL;
  mpstSong    = orxNULL;
  
  zMod = orxResource_Locate("Mod", orxConfig_GetString("Mod"));

  if(zMod)
  {
    orxHANDLE hMod;

    hMod = orxResource_Open(zMod, orxFALSE);

    if(hMod != orxHANDLE_UNDEFINED)
    {
      orxU8 *pu8Buffer;
      orxS64 s64Size;

      s64Size = orxResource_GetSize(hMod);

      pu8Buffer = (orxU8 *)orxMemory_Allocate((orxU32)s64Size, orxMEMORY_TYPE_TEMP);

      if(pu8Buffer)
      {
        mpstPlayer = KSND_CreatePlayer(44100);

        if(mpstPlayer)
        {
          KSND_SetPlayerQuality(mpstPlayer, 4);

          if(orxResource_Read(hMod, s64Size, pu8Buffer, orxNULL, orxNULL) == s64Size)
          {
            mpstSong = KSND_LoadSongFromMemory(mpstPlayer, pu8Buffer, (int)s64Size);
            UpdateMod();
            KSND_PlaySong(mpstPlayer, mpstSong, 0);
          }
        }

        orxMemory_Free(pu8Buffer);
      }

      orxResource_Close(hMod);
    }
  }
}

void Mod::OnDelete()
{
  if(mpstPlayer)
  {
    KSND_Stop(mpstPlayer);

    if(mpstSong)
    {
      KSND_FreeSong(mpstSong);
    }

    KSND_FreePlayer(mpstPlayer);
  }
}

void Mod::Update(const orxCLOCK_INFO &_rstInfo)
{
  UpdateMod();
}

void Mod::UpdateMod()
{
  if(mpstPlayer)
  {
    PushConfigSection();
    KSND_SetVolume(mpstPlayer, (int)(128.0f * orxConfig_GetFloat("Volume") * orxSound_GetBusGlobalVolume(orxString_Hash(orxConfig_GetString("Bus")))));
    PopConfigSection();
  }
}
