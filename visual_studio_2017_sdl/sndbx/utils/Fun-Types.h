/*
 * Fun_Types.h
 *
 * Created: 2014/04/26 10:04:01
 *  Author: Deon Marais
 */


#ifndef FUN_TYPES_H_
#define FUN_TYPES_H_


#include <time.h>
#include "C-FPoint.h"

typedef V	(*_V_PFN_V_)					( V );
typedef V	(*_V_PFN_H_)					( H );
typedef V	(*_V_PFN_PV_ )					( PV );
typedef V	(*_V_PFN_U8_)					( U8 );
typedef V	(*_V_PFN_U32_)					( U32 );
typedef V	(*_V_PFN_PCV_)					( PCV );
typedef V	(*_V_PFN_PCC_)					( PCC );
typedef V	(*_V_PFN_PCU8_U16_)				( PCU8, U16 );
typedef V   (*_V_PFN_PC_PV_)				( PC, PV );
typedef V   (*_V_PFN_PC_PC_)				( PC, PC );
typedef V   (*_V_PFN_PC_U16_)				( PC, U16 );
typedef V   (*_V_PFN_PC_U32_)				( PC, U32 );
typedef V   (*_V_PFN_PV_PC_U32_)			( PV, PC, U32 );
typedef V   (*_V_PFN_PCU8_ST_)				( PCU8, ST );
typedef V	(*_V_PFN_ST_)					( ST );

typedef B	(*_B_PFN_PV_)					( PV );
typedef B	(*_B_PFN_U8_)					( U8 );
typedef B	(*_B_PFN_U8_U8_)				( U8, U8 );
typedef B	(*_B_PFN_PU8_)					( PU8 );
typedef B   (*_B_PFN_PCC_PCC_)				( PCC, PCC );
typedef B   (*_B_PFN_S32_)					( S32 );

typedef C	(*_C_PFN_C_)					( C );
typedef UC  (*_UC_PFN_PC_PV_)				( PC, PV );
typedef UC  (*_UC_PFN_PC_PC_)				( PC, PC );
typedef UC  (*_UC_PFN_PC_PC_PC_)			( PC, PC, PC );

typedef S   (*_S_PFN_PCC_PCC_)				( PCC, PCC );

typedef I   (*_I_PFN_I_)					( I );
typedef I   (*_I_PFN_PCC_PCC_)				( PCC, PCC );

typedef UI  (*_UI_PFN_PCC_PCC_)				( PCC, PCC );


typedef S8	(*_S8_PFN_PV_PCC_)				( PV, PCC );
typedef U8	(*_U8_PFN_PC_PV_)				( PC, PV );
typedef U32 (*_U32_PFN_PCC_U32_)			( PCC, U32 );

typedef ST  (*_ST_PFN_V_)					( V );
typedef ST  (*_ST_PFN_PCUC_ST_)				( PCUC, ST );

typedef H	(*_H_PFN_V_)					( V );

typedef V	(*_V_PFN__V_PFN_V__)			( _V_PFN_V_ );
typedef V   (*_V_PFN__V_PFN_PC_U32__PC_U32_)( _V_PFN_PC_U32_, PC, U32 );
typedef V	(*_V_PFN__V_PFN_H__H_)			( _V_PFN_H_, H );

/* Functions with void params returning simple base types */
typedef B		(*_B_PFN_V_)				( V );
typedef C		(*_C_PFN_V_)				( V );
typedef SC		(*_SC_PFN_V_)				( V );
typedef S8		(*_S8_PFN_V_)				( V );
typedef UC		(*_UC_PFN_V_)				( V );
typedef U8		(*_U8_PFN_V_)				( V );
typedef SS		(*_SS_PFN_V_)				( V );
typedef S16		(*_S16_PFN_V_)				( V );
typedef US		(*_US_PFN_V_)				( V );
typedef U16		(*_U16_PFN_V_)				( V );
typedef I   	(*_I_PFN_V_)				( V );
typedef SI   	(*_SI_PFN_V_)				( V );
typedef UI   	(*_UI_PFN_V_)				( V );
typedef SL		(*_SL_PFN_V_)				( V );
typedef S32		(*_S32_PFN_V_)				( V );
typedef UL		(*_UL_PFN_V_)				( V );
typedef U32		(*_U32_PFN_V_)				( V );
typedef SLL		(*_SLL_PFN_V_)				( V );
typedef S64		(*_S64_PFN_V_)				( V );
typedef ULL		(*_ULL_PFN_V_)				( V );
typedef U64		(*_U64_PFN_V_)				( V );

typedef PC		(*_PC_PFN_V_)				( V );
typedef PCC		(*_PCC_PFN_V_)				( V );

typedef time_t	(*_time_t_PFN_V_)			( V );
typedef __time32_t	(*___time32_t_PFN_V_)	( V );
typedef __time64_t	(*___time64_t_PFN_V_)	( V );

typedef FP		(*_FP_PFN_V_)				( V );
typedef FP32	(*_FP32_PFN_V_)				( V );
typedef FP64	(*_FP64_PFN_V_)				( V );

#endif /* FUN_TYPES_H_ */
