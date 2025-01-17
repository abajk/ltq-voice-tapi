/******************************************************************************

                            Copyright (c) 2014, 2016
                        Lantiq Beteiligungs-GmbH & Co.KG

  For licensing information, see the file 'LICENSE' in the root folder of
  this software module.

*******************************************************************************/

/**
   \file drv_tapi_fxo_ll_interface.h
   TAPI FXO interface to the DAA abstraction driver
*/

#ifndef _DRV_TAPI_FXO_IO_H
#define _DRV_TAPI_FXO_IO_H

#include <ifx_types.h>

typedef struct {
   IFX_return_t (*Init)    (IFX_uint16_t nDAA);
   IFX_return_t (*osiCfg)  (IFX_uint32_t nOsiMaxTime);
   IFX_return_t (*fhCfg)   (IFX_uint32_t nFlashHookTime);
   IFX_return_t (*fhSet)   (IFX_uint16_t nDAA);
   IFX_return_t (*hookSet) (IFX_uint16_t nDAA, IFX_TAPI_FXO_HOOK_t  nHookState);
   IFX_return_t (*hookGet) (IFX_uint16_t nDAA, IFX_TAPI_FXO_HOOK_t *pHookState);
   IFX_return_t (*apohGet) (IFX_uint16_t nDAA, IFX_enDis_t *pApohState);
   IFX_return_t (*polGet)  (IFX_uint16_t nDAA, IFX_enDis_t *pPolState);
   IFX_return_t (*batGet)  (IFX_uint16_t nDAA, IFX_enDis_t *pBatState);
   IFX_return_t (*ringGet) (IFX_uint16_t nDAA, IFX_enDis_t *pRingState);
} IFX_TAPI_DRV_CTX_DAA_t;


extern IFX_int32_t IFX_TAPI_Register_DAA_Drv(
                        IFX_TAPI_DRV_CTX_DAA_t *pDAA);

extern IFX_int32_t IFX_TAPI_FXO_Event_Dispatch(
                        IFX_int32_t nDAA,
                        IFX_TAPI_EVENT_t *pEvent);

#endif /* _DRV_TAPI_FXO_IO_H */
