/*
 * Variant_Lib.c
 *
 * Created: 2014/04/27 01:44:50
 *  Author: Deon Marais
 */

#include "Variant-Lib.h"
#include "Fun-Types.h"
#include "utils.h"
#include "RTC.h"
#include "Critical.h"

#include <stdio.h>
#include <string.h>

#undef ENTER_CRITICAL_REGION
#undef LEAVE_CRITICAL_REGION
#define ENTER_CRITICAL_REGION()
#define LEAVE_CRITICAL_REGION()

//extern V Lock_vfprintf_r	( V );
//extern V UnLock_vfprintf_r	( V );

#define LOCK_FPRINTF()
#define UNLOCK_FPRINTF()

#if 1
#define CONV_BASE 0
#else
#define CONV_BASE 10
#endif

I Var_StrToVar ( PCC str, VarP vp, eVar_t vt )
{
	I retVal = 1;

	if( vt <= V_FP64 )
	{
		LOCK_FPRINTF();
		switch( vt )
		{
			case V_B:
				retVal = ParseB( str, vp.pb );
			break;
#if CHAR_MIN == 0
			case V_C:
#endif
			case V_SC:
			case V_S8:
				retVal = ParseSC( str, vp.psc, CONV_BASE );
			break;
#if CHAR_MAX == 255
			case V_C:
#endif
			case V_UC:
			case V_U8:
				retVal = ParseUC( str, vp.puc, CONV_BASE );
			break;
			case V_SS:
			case V_S16:
				retVal = ParseSS( str, vp.pss, CONV_BASE );
			break;
			case V_US:
			case V_U16:
				retVal = ParseUS( str, vp.pus, CONV_BASE );
			break;
			case V_SI:
				retVal = ParseSI( str, vp.psi, CONV_BASE );
			break;
			case V_UI:
				retVal = ParseUI( str, vp.pui, CONV_BASE );
			break;
			case V_SL:
			case V_S32:
				retVal = ParseSL( str, vp.psl, CONV_BASE );
			break;
			case V_UL:
			case V_U32:
				retVal = ParseUL( str, vp.pul, CONV_BASE );
			break;
			case V_SLL:
			case V_S64:
				retVal = ParseSLL( str, vp.psll, CONV_BASE );
			break;
			case V_ULL:
			case V_U64:
				retVal = ParseULL( str, vp.pull, CONV_BASE );
			break;
#if (FP_BITS == 32)
			case V_FP:
#endif
			case V_FP32:
				retVal = ParseFLT( str, vp.pfp32 );
			break;
#if (FP_BITS == 64)
			case V_FP:
#endif
			case V_FP64:
				retVal = ParseDBL( str, vp.pfp64 );
			break;
			default:
				retVal = 0;
			break;
		}
		UNLOCK_FPRINTF();
	}
	else
	{
#if 1
		switch( vt )
		{
			case V_TIME_OFFSET:
			{
				TimeRec tr;
				UI day, hour, min, sec;
				I i = sscanf( str, "%ud%u:%u:%u", &day, &hour, &min, &sec );
				tr.day = day < 256 ? day : 255;
				tr.hour = hour < 24 ? hour : 23;
				tr.min = min < 60 ? min : 59;
				if( day >= 1)
					tr.sec = 0;
				else
					tr.sec = sec < 60 ? sec : 59;
				*vp.ptime = RTC_TimeRecToTimeOffset(&tr);
			}
			break;
			case V_DATE_TIME:
			{
				TimeRec tr;
				UI year, month, day, hour, min, sec;
				I i = sscanf( str, "%u/%u/%u %u:%u:%u", &year, &month, &day, &hour, &min, &sec );
				tr.year = year;
				tr.month = month;
				tr.day = day;
				tr.hour = hour;
				tr.min = min;
				tr.sec = sec;
				if( RTC_IsTimeRecValid( &tr))
					*vp.ptime = RTC_TimeRecToTime(&tr);
			}
			break;
			case V_YN:
				if( !strcmp( str, "Y") )
					*vp.pb = 1;
				else if( !strcmp(str, "N") )
					*vp.pb = 0;
				else
					retVal = 0;
			break;
			default:
				retVal = 0;
			break;
		}
#endif
	}

	return retVal;
}

I Var_VarToStr ( PC s, PCC pFmt, PCVar pv, eVar_t vt )
{
	switch( vt )
	{
		case V_C:
		case V_SC:
		case V_S8:
		case V_UC:
		case V_U8:		
			return sprintf( s, pFmt, pv->c );
		case V_SS:
		case V_S16:
		case V_US:
		case V_U16:		
			return sprintf( s, pFmt, pv->ss );
		case V_SL:
		case V_S32:
		case V_UL:
		case V_U32:		
			return sprintf( s, pFmt, pv->sl );
		case V_SI:
		case V_UI:		
			return sprintf( s, pFmt, pv->si );
		case V_SLL:
		case V_S64:
		case V_ULL:
		case V_U64:		
			return sprintf( s, pFmt, pv->sll );
#if (FP_BITS == 32)
		case V_FP:
#endif
		case V_FP32:
		{
			ENTER_CRITICAL_REGION();
			FP v = pv->fp32;
			LEAVE_CRITICAL_REGION();
			return sprintf( s, pFmt, (FP64)v );
		}
#if (FP_BITS == 64)
		case V_FP:
#endif
		case V_FP64:
		{
			ENTER_CRITICAL_REGION();
			FP64 v = pv->fp64;
			LEAVE_CRITICAL_REGION();
			return sprintf( s, pFmt, v);
		}
		case V_YN:		return sprintf( s, pFmt, pv->b ? 'Y' : 'N' );
		case V_STRING:
		case V_CSTRING:	return sprintf( s, pFmt, pv->c );
#if 1
		case V_TIME_OFFSET:
		{
			RTC_TimeString_t timeStr;
			TimeRec tr;
			RTC_TimeOffsetToTimeRec( pv->time, &tr );
			RTC_MakeTimeStringTimeRec( TSO_DDdhhmmss, &timeStr, &tr );
			return sprintf( s, "%s", timeStr );
		}
		case V_DATE_TIME:
		{

		}
		/* No Break */
#endif
		default:		return 0;
	}
}

I Var_VarToStrn ( PC s, PCC pFmt, PCVar pv, ST n, eVar_t vt )
{
	switch( vt )
	{
		case V_C:
		case V_SC:
		case V_S8:
		case V_UC:
		case V_U8:
			return snprintf( s, n, pFmt, pv->c );
		case V_SS:
		case V_S16:
		case V_US:
		case V_U16:		
			return snprintf( s, n, pFmt, pv->ss );
		case V_SL:
		case V_S32:
		case V_UL:
		case V_U32:		
			return snprintf( s, n, pFmt, pv->sl );
		case V_SI:
		case V_UI:		
			return snprintf( s, n, pFmt, pv->si );
		case V_SLL:
		case V_S64:
		case V_ULL:
		case V_U64:		
			return snprintf( s, n, pFmt, pv->sll );
#if (FP_BITS == 32)
		case V_FP:
#endif
		case V_FP32:
		{
			ENTER_CRITICAL_REGION();
			FP64 v = pv->fp32;
			LEAVE_CRITICAL_REGION();
			return snprintf( s, n, pFmt, (FP64)v );
		}
#if (FP_BITS == 64)
		case V_FP:
#endif
		case V_FP64:
		{
			ENTER_CRITICAL_REGION();
			FP64 v = pv->fp64;
			LEAVE_CRITICAL_REGION();
			return snprintf( s, n, pFmt, v);
		}
		case V_YN:
			return snprintf( s, n, pFmt, pv->b ? 'Y' : 'N' );
		case V_STRING:
		case V_CSTRING:
			return snprintf( s, n, pFmt, pv->pc );
#if 1
		case V_TIME_OFFSET:
		{
			RTC_TimeString_t timeStr;
			TimeRec tr;
			RTC_TimeOffsetToTimeRec( pv->time, &tr );
			RTC_MakeTimeStringTimeRec( TSO_DDdhhmmss, &timeStr, &tr );
			return snprintf( s, n, "%s", timeStr );
		}
		case V_TIME:
			return snprintf( s, n, pFmt, pv->time );
		case V_DATE_TIME:
		{

		}
		/* No Break */
#endif
		default:		return 0;
	}
}

V Var_AssignVar ( PV pvTo, PCVar pvFr, eVar_t vt )
{
	if (!pvTo || !pvFr)
		return;

	switch( vt )
	{
		case V_B:
			*(PB)pvTo = pvFr->b;
		break;
		case V_C:
		case V_SC:
		case V_S8:
		case V_UC:
		case V_U8:
			*(PC)pvTo = pvFr->c;
		break;
		case V_SS:
		case V_S16:
		case V_US:
		case V_U16:
			*(PSS)pvTo = pvFr->ss;
		break;
		case V_SI:
		case V_UI:
			*(PSI)pvTo = pvFr->si;
		break;
		case V_SL:
		case V_S32:
		case V_UL:
		case V_U32:
			*(PSL)pvTo = pvFr->sl;
		break;
		case V_SLL:
		case V_S64:
		case V_ULL:
		case V_U64:
			*(PSLL)pvTo = pvFr->sll;
		break;
#if (FP_BITS == 32)
		case V_FP:
#endif
		case V_FP32:
			*(PFP32)pvTo = pvFr->fp32;
		break;
#if (FP_BITS == 64)
		case V_FP:
#endif
		case V_FP64:
			*(PFP64)pvTo = pvFr->fp64;
		break;
		case V_TIME:
			*(time_t*)pvTo = pvFr->time;
		break;
		case V_TIME32:
			*(__time32_t*)pvTo = pvFr->time32;
			break;
		case V_TIME64:
			*(__time64_t*)pvTo = pvFr->time64;
			break;
		case V_CSTRING:
			*(PCC*)pvTo = pvFr->pcc;
		break;
		default:
		break;
	}
}

V Var_AssignVarFrFun ( PV pvTo, _VarXT_PFN_V_ pFun, eVar_t vt )
{
	if( !pvTo || !pFun )
		return;

	switch( vt )
	{
		case V_B:		*(PB)pvTo	= ((_B_PFN_V_)pFun)();			break;
		case V_C:		*(PC)pvTo = ((_C_PFN_V_)pFun)();			break;
		case V_SC:		*(PSC)pvTo = ((_SC_PFN_V_)pFun)();		break;
		case V_S8:		*(PS8)pvTo = ((_S8_PFN_V_)pFun)();		break;
		case V_UC:		*(PUC)pvTo = ((_UC_PFN_V_)pFun)();		break;
		case V_U8:		*(PU8)pvTo = ((_U8_PFN_V_)pFun)();		break;
		case V_SS:		*(PSS)pvTo = ((_SS_PFN_V_)pFun)();		break;
		case V_S16:		*(PS16)pvTo = ((_S16_PFN_V_)pFun)();		break;
		case V_US:		*(PUS)pvTo = ((_US_PFN_V_)pFun)();		break;
		case V_U16:		*(PU16)pvTo = ((_U16_PFN_V_)pFun)();		break;
		case V_SI:		*(PSI)pvTo = ((_SI_PFN_V_)pFun)();		break;
		case V_UI:		*(PUI)pvTo = ((_UI_PFN_V_)pFun)();		break;
		case V_SL:		*(PSL)pvTo = ((_SL_PFN_V_)pFun)();		break;
		case V_S32:		*(PS32)pvTo = ((_S32_PFN_V_)pFun)();		break;
		case V_UL:		*(PUL)pvTo = ((_UL_PFN_V_)pFun)();		break;
		case V_U32:		*(PU32)pvTo = ((_U32_PFN_V_)pFun)();		break;
		case V_SLL:		*(PSLL)pvTo = ((_SLL_PFN_V_)pFun)();		break;
		case V_S64:		*(PS64)pvTo = ((_S64_PFN_V_)pFun)();		break;
		case V_ULL:		*(PULL)pvTo = ((_ULL_PFN_V_)pFun)();		break;
		case V_U64:		*(PU64)pvTo = ((_U64_PFN_V_)pFun)();		break;
		case V_FP:		*(PFP)pvTo = ((_FP_PFN_V_)pFun)();		break;
		case V_FP32:	*(PFP32)pvTo = ((_FP32_PFN_V_)pFun)();	break;
		case V_FP64:	*(PFP64)pvTo = ((_FP64_PFN_V_)pFun)();	break;
		case V_TIME:	*(time_t*)pvTo = ((_time_t_PFN_V_)pFun)(); break;
		case V_TIME32:	*(__time32_t*)pvTo = ((___time32_t_PFN_V_)pFun)(); break;
		case V_TIME64:	*(__time64_t*)pvTo = ((___time64_t_PFN_V_)pFun)(); break;
		case V_STRING:	*(PC*)pvTo = ((_PC_PFN_V_)pFun)();		break;
		case V_CSTRING:	*(PCC*)pvTo = ((_PCC_PFN_V_)pFun)();		break;
		default:
		break;
	}
}

I Var_VarCmp ( PCVar pv1, PCVar pv2, eVar_t vt )
{
	if( !pv1 || !pv2 )
		return 0;

	ST size;
	switch( vt )
	{
		case V_B:
			size = sizeof(B);
		break;
		case V_C:
		case V_SC:
		case V_S8:
		case V_UC:
		case V_U8:
			size = sizeof(U8);
		break;
		case V_SS:
		case V_S16:
		case V_US:
		case V_U16:
			size = sizeof(U16);
		break;
		case V_SI:
		case V_UI:
			size = sizeof(UI);
		break;
		case V_SL:
		case V_S32:
		case V_UL:
		case V_U32:
			size = sizeof(U32);
		break;
		case V_SLL:
		case V_S64:
		case V_ULL:
		case V_U64:
			size = sizeof(U64);
		break;
#if (FP_BITS == 32)
		case V_FP:
#endif
		case V_FP32:
			size = sizeof(FP32);
		break;
#if (FP_BITS == 64)
		case V_FP:
#endif
		case V_FP64:
			size = sizeof(FP64);
		break;
		case V_TIME:
			size = sizeof(time_t);
		break;
		case V_TIME32:
			size = sizeof(__time32_t);
		break;
		case V_TIME64:
			size = sizeof(__time64_t);
		break;
		case V_STRING:
		case V_CSTRING:
//			return pv1->pcc == pv2->pcc ? 0 : strcmp( pv1->pcc, pv2->pcc );
			if (!pv1->pcc || !pv2->pcc)
				return 0;
			return strcmp( pv1->pcc, pv2->pcc );
		default:
			size = 0;
		break;
	}
	return memcmp( &pv1->b, &pv2->b, size );
}
