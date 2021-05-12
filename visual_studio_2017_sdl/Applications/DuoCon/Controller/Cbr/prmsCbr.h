#ifndef PRMSCBR_H
#define PRMSCBR_H

#include "C-FPoint.h"
#include "src/Control/pidGeneric.h"

typedef struct {
	FP	tCmpFctBrd;
} CbrPressCalib_t, *PCbrPressCalib_t;
typedef const CbrPressCalib_t	CCbrPressCalib_t;
typedef CCbrPressCalib_t *		PCCbrPressCalib_t;
typedef const PCCbrPressCalib_t	CPCCbrPressCalib_t;

extern CPCCbrPressCalib_t	pCbrPressCalib;
extern CPCCbrPressCalib_t	pCbrPressCalibMin;
extern CPCCbrPressCalib_t	pCbrPressCalibMax;

typedef struct {
	FP 		motorSpeedMan;
	FP		motorSpeedAppr;
	FP		pressureSensorFullScale;
	FP		pressureSensorNormalisedFullScale;
	U16		motionSensor_ppmm;
	B		diagnosticsOn;
} CbrPressCfg_t, *PCbrPressCfg_t;
typedef const CbrPressCfg_t		CCbrPressCfg_t;
typedef CCbrPressCfg_t *		PCCbrPressCfg_t;
typedef const PCCbrPressCfg_t	CPCCbrPressCfg_t;

extern CPCCbrPressCfg_t pCbrPressCfg;
extern CPCCbrPressCfg_t pCbrPressCfgMin;
extern CPCCbrPressCfg_t pCbrPressCfgMax;

typedef struct {
	PCCbrPressCfg_t pCfg;
	PCCbrPressCfg_t pMin;
	PCCbrPressCfg_t pMax;
} CbrPressSetting_t;
extern CbrPressSetting_t const * const pCbrPressSetting;

typedef struct {
	FP			startPressure;
	FP			breakPressureDrop;
	FP			specific[2];
	FP			setPoint;
	PidGains	pid;
	C			sampleNb[16];
} CbrTestCfg_t, *PCbrTestCfg_t;
typedef const CbrTestCfg_t		CCbrTestCfg_t;
typedef CCbrTestCfg_t *			PCCbrTestCfg_t;
typedef const PCCbrTestCfg_t	CPCCbrTestCfg_t;

extern CPCCbrTestCfg_t
	pCbrTestCfgCbr,
	pCbrTestCfgUcs,
	pCbrTestCfgIts,
	pCbrTestCfgMrshl;

extern CPCCbrTestCfg_t
	pCbrTestCfgCbrMin,
	pCbrTestCfgUcsMin,
	pCbrTestCfgItsMin,
	pCbrTestCfgMrshlMin;

extern CPCCbrTestCfg_t
	pCbrTestCfgCbrMax,
	pCbrTestCfgUcsMax,
	pCbrTestCfgItsMax,
	pCbrTestCfgMrshlMax;

typedef struct {
	PCCbrTestCfg_t pCfg;
	PCCbrTestCfg_t pMin;
	PCCbrTestCfg_t pMax;
} CbrTestSetting_t;
extern CbrTestSetting_t const * const pCbrTestSettingCbr;
extern CbrTestSetting_t const * const pCbrTestSettingUcs;
extern CbrTestSetting_t const * const pCbrTestSettingIts;
extern CbrTestSetting_t const * const pCbrTestSettingMrshl;

/* Test getters and setters */
extern FP Cbr_TestCfgKpGet( PCCbrTestCfg_t pcFr );
extern FP Cbr_TestCfgKiGet( PCCbrTestCfg_t pcFr );
extern FP Cbr_TestCfgKdGet( PCCbrTestCfg_t pcFr );

extern V Cbr_TestCfgStartPressureSave( PCCbrTestCfg_t pcTo, FP startPressure);
extern V Cbr_TestCfgBreakPressureDropSave( PCCbrTestCfg_t pcTo, FP breakPressureDrop );
extern V Cbr_TestCfgSpecific0Save( PCCbrTestCfg_t pcTo, FP specific0 );
extern V Cbr_TestCfgSpecific1Save( PCCbrTestCfg_t pcTo, FP specific1 );
extern V Cbr_TestCfgSpecific01Save(PCCbrTestCfg_t pcTo, FP specific0, FP specific1 );
extern V Cbr_TestCfgSetpointSave( PCCbrTestCfg_t pcTo, FP setPoint);
extern V Cbr_TestCfgKpSave( PCCbrTestCfg_t pcTo, FP kp);
extern V Cbr_TestCfgKiSave( PCCbrTestCfg_t pcTo, FP ki);
extern V Cbr_TestCfgKdSave( PCCbrTestCfg_t pcTo, FP kd);
extern V Cbr_TestCfgSampleNbSave( PCCbrTestCfg_t pcTo, PCC sampleNb );

#define PRMS_DEFAULTED 0x2

extern UI	Cbr_PrmsInit			( V );
extern V	Cbr_PressCalibSave		( PCCbrPressCalib_t pc );
extern V	Cbr_PressCfgSave 		( PCCbrPressCfg_t pc );
extern V 	Cbr_PressSpeedManSave	( FP speedPerc );
extern V 	Cbr_PressSpeedApprSave	( FP speedPerc );

extern V	Cbr_TestCfgSave			( PCCbrTestCfg_t pcTo, PCCbrTestCfg_t pcFr );
extern V 	Cbr_TestCfgGet 			( PCbrTestCfg_t pCfg, PCCbrTestCfg_t pcFr );

#endif

