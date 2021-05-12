#ifndef DDO_H
#define DDO_H

#include "C-Types.h"

extern V Ddo_MotorOnForward ( V );
extern V Ddo_MotorOnReverse ( V );
extern V Ddo_MotorOff 		( V );

extern PCC Ddo_MotorForwardGetStr	( V );
extern PCC Ddo_MotorReverseGetStr	( V );
extern PCC Ddo_SolValveGetStr 		( V );
extern PCC Ddo_BuzzerOnGetStr		( V );

#endif
