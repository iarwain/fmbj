/**
 * @file SFXR.cpp
 * @date 2-Jun-2021
 */

#include "SFXR.h"

static orxSTATUS orxFASTCALL EventHandler(const orxEVENT *_pstEvent)
{
  orxOBJECT* pstSender;

  pstSender = orxOBJECT(_pstEvent->hSender);
  if(pstSender)
  {
    SFXR *poSFXR;

    poSFXR = ScrollCast<SFXR *>((ScrollObject *)orxObject_GetUserData(pstSender));
    poSFXR->FillBuffer(((orxSOUND_EVENT_PAYLOAD *)_pstEvent->pstPayload)->stStream.stPacket);
  }

  return orxSTATUS_SUCCESS;
}

void SFXR::FillBuffer(orxSOUND_STREAM_PACKET &_rstPacket)
{
  //! TODO: Update packet
}

void SFXR::OnCreate()
{
#define SFXR_DEFINE(Type, TYPE, Name) mstParams.##Name = orxConfig_Get##Type(#Name);
#include "SFXR.inc"
#undef SFXR_DEFINE

  if(orxEvent_SetHandlerIDFlags(EventHandler, orxEVENT_TYPE_SOUND, orxNULL, orxEVENT_KU32_FLAG_ID_NONE, orxEVENT_KU32_FLAG_ID_NONE) == orxSTATUS_FAILURE)
  {
    orxEvent_AddHandler(orxEVENT_TYPE_SOUND, EventHandler);
    orxEvent_SetHandlerIDFlags(EventHandler, orxEVENT_TYPE_SOUND, orxNULL, orxEVENT_GET_FLAG(orxSOUND_EVENT_PACKET), orxEVENT_KU32_MASK_ID_ALL);
  }
}

void SFXR::OnDelete()
{
}
