#ifndef _RTC_H
#define _RTC_H

#include <time.h>
#include "C-FPoint.h"

#define TICKS_PER_SECOND 1000u

//#undef CLOCKS_PER_SEC
//#define CLOCKS_PER_SEC  TICKS_PER_SECOND

#define SECONDS_BETWEEN_Y1970_Y2012 ((2012-1970)*365 + (2012-1970)/4)*86400

typedef struct{
    U16 year;   /* 2000.... */
    U8  month;  /* 1..12    */
    U8  day;    /* 1..31    */
    U8  hour;   /* 0..23    */
    U8  min;    /* 0..59    */
    U8  sec;    /* 0..59    */
    U16 ms;     /* 0..999   */
} TimeRec;

/* Conversion functions             */

extern time_t	RTC_TimeRecToTime       ( TimeRec *pTr );
extern time_t	RTC_TimeRecToTimeOffset ( TimeRec *pTr );
extern V		RTC_TimeOffsetToTimeRec ( time_t tOffset, TimeRec * pTr );
//extern V 		RTC_TimeOffsetToTimeRec ( __time32_t tOffset, TimeRec * pTr );
extern V		RTC_TimeToTimeRec       ( time_t tme, TimeRec *pTr );
extern V		RTC_TimeRecToTmStruct   ( TimeRec *tr, struct tm *pTm );
extern V		RTC_TmStructToTimeRec   ( struct tm *tms, TimeRec *pTr );
extern U32		RTC_TimeToFatTime       ( time_t tme );
extern V		RTC_FatTimeToTimeRec    ( U32 fatTime, TimeRec *pTr );
extern time_t	RTC_FatTimeToTime       ( U32 fatTime );

/* Getter functions                 */

extern V    RTC_GetRtc              ( TimeRec * tr );
extern FP64 RTC_TimeNow_D_HMSsss    ( V );        /* days since 1900/01/02 00:00:00   */
extern U32  RTC_GetFatTime          ( V );

/* RTC string conversion functions  */

#define TSO_YEAR    0x40
#define TSO_MONTH   0x20
#define TSO_DAY     0x10
#define TSO_HOUR    0x08
#define TSO_MIN     0x04
#define TSO_SEC     0x02
#define TSO_MSEC    0x01

typedef enum {
    TSO_hhmmss			= (TSO_HOUR|TSO_MIN|TSO_SEC),
	TSO_TIME            = (TSO_HOUR|TSO_MIN|TSO_SEC|TSO_MSEC),
	TSO_DATE            = (TSO_YEAR|TSO_MONTH|TSO_DAY),
	TSO_YYYYMMDD_hhmm   = (TSO_YEAR|TSO_MONTH|TSO_DAY|TSO_HOUR|TSO_MIN),
	TSO_YYYYMMDD_hhmmss = (TSO_YEAR|TSO_MONTH|TSO_DAY|TSO_HOUR|TSO_MIN|TSO_SEC),
	TSO_ALL             = (TSO_YEAR|TSO_MONTH|TSO_DAY|TSO_HOUR|TSO_MIN|TSO_SEC|TSO_MSEC),
	TSO_DDdhhmmss,
	TSO_UPTIME,
	TSO_MMM_dd_yyyy,
	TSO_MMM_dd_HH_mm,
	TSO_YYYYMMDDhhmmssms,
} RTC_TIMESTRING_OPTS;

typedef C RTC_TimeString_t[24];

/*
    Returns a pointer to a string with the following maximal format
    YYYY/MM/DD hh:mm:ss.sss == 23 chars
*/
#define RTC_TimeStringTimeRec(tso, pTs) RTC_MakeTimeStringTimeRec( tso, 0, pTs )
extern PC	RTC_TimeStringTime           ( RTC_TIMESTRING_OPTS tso, time_t time );
extern PC 	RTC_TimeStringTmStruct       ( RTC_TIMESTRING_OPTS tso, struct tm *ptm );
extern PC 	RTC_TimeString               ( RTC_TIMESTRING_OPTS tso );
extern PC 	RTC_MakeTimeStringTimeRec    ( RTC_TIMESTRING_OPTS tso, RTC_TimeString_t *pTs, TimeRec *pTr );
extern PC 	RTC_MakeTimeStringTime       ( RTC_TIMESTRING_OPTS tso, RTC_TimeString_t *pTs, time_t time );
extern PC 	RTC_MakeTimeStringTmStruct   ( RTC_TIMESTRING_OPTS tso, RTC_TimeString_t *pTs, struct tm *ptm );
extern PC 	RTC_MakeTimeString           ( RTC_TIMESTRING_OPTS tso, RTC_TimeString_t *pTs );

extern PC	RTC_MakeDurationString		 ( PC pStr, U32 ms );

/* Depricated functions             */

extern S64  RTC_DateTime_BCD    ( TimeRec * tr );
extern S64  RTC_DateTimeNow_BCD ( V );

/* Utility functions                */

extern U32		RTC_GetUpTime       ( V );			/* Seconds since system startup             */
extern time_t	RTC_GetTime			( V );
extern I		RTC_DaysInMonth     ( UF8 m, UF16 y );
extern B		RTC_IsTimeRecValid  ( const TimeRec *tr );


/* RTC and time setting functions   */

extern V	RTC_SetRtc     ( TimeRec *tr );		/* Set RTC from TimeRec     */
extern V	RTC_SetTime    ( time_t time );		/* Set RTC from time_t      */

/* Low level functions              */
extern V	RTC_UpdateRtc	( V );				/* Called by system tick    */

#endif
