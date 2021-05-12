#ifndef CTRLRCBRZERO_H
#define CTRLRCBRZERO_H

#include "C-Fpoint.h"
#include "controllerCbr.h"

extern const CbrCtrlrCtdaFuns_t ctrlrCbrZeroFns;

extern eCbrCtrlrState_t Cbr_CtrlrZeroStateGet	( V );
extern PCC CtrlrCbrZero_StateGetStr ( eCbrCtrlrState_t state );

#endif
