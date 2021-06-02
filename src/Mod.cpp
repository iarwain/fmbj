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
  meStatus    = orxSOUND_STATUS_STOP;

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
  if(mpstPlayer && mpstSong)
  {
    orxSOUND *pstSound;

    pstSound = orxObject_GetLastAddedSound(GetOrxObject());

    if(pstSound)
    {
      orxSOUND_STATUS eNewStatus;

      KSND_SetVolume(mpstPlayer, (int)(128.0f * orxSound_GetVolume(pstSound) * orxSound_GetBusGlobalVolume(orxSound_GetBusID(pstSound))));

      eNewStatus = orxSound_GetStatus(pstSound);

      switch(eNewStatus)
      {
        case orxSOUND_STATUS_PLAY:
        {
          // Stopped?
          if(meStatus == orxSOUND_STATUS_STOP)
          {
            KSND_PlaySong(mpstPlayer, mpstSong, 0);
          }
          else if(meStatus == orxSOUND_STATUS_PAUSE)
          {
            KSND_Pause(mpstPlayer, 0);
          }
          break;
        }

        case orxSOUND_STATUS_PAUSE:
        {
          // Playing?
          if(meStatus == orxSOUND_STATUS_PLAY)
          {
            KSND_Pause(mpstPlayer, 1);
          }
          break;
        }

        case orxSOUND_STATUS_STOP:
        {
          // Not stopped?
          if(meStatus != orxSOUND_STATUS_STOP)
          {
            KSND_Stop(mpstPlayer);
          }
          break;
        }
      }

      meStatus = eNewStatus;
    }
  }
}
