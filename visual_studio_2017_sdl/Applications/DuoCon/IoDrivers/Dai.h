#ifndef DAI_H
#define DAI_H

#include "C-FPoint.h"

extern V	Dai_Init			( B pressCbr );
extern FP	Dai_NewPressureGet	( V );
extern FP	Dai_PressureGet		( V );
extern FP	Dai_PressureUiGet	( V );
extern FP	Dai_PressureUiPecentageGet( V );


#endif
