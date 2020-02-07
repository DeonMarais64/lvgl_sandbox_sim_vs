#include "Critical.h"
#include "rtc.h"
//#include "utilsStr.h"
#include "datelib.h"

#define SECONDS_BETWEEN_Y1970_Y2000 ((2000-1970)*365 + (2000-1970)/4)*86400
#define CAL_DAYS_AT_1900            693598
#define CAL_DAYS_AT_1970            719165

static TimeRec	rtc		= {2000, 1, 1, 0, 0, 0, 0 };
static time_t	sysTime	= SECONDS_BETWEEN_Y1970_Y2000;
static U32		upTime;

#if 0
static const U32 calDaysAt1900_01_01 = 693598;     /* Gregorian Calendar Days at 1900/01/01 00:00:00 */
static const U32 calDaysAt1970_01_01 = 719165;     /* Gregorian Calendar Days at 1970/01/01 00:00:00 */
#endif

/**
-----------------------------------------------------------------------------------------------------------------------------------
Conversion functions
*/

/*
    Returns the number of seconds since 1970/01/01 00:00:00 for a given TimeRec
*/
time_t RTC_TimeRecToTime ( TimeRec *pTr )
{
    time_t _time;
    struct tm ansiiTime;

    LoadDateStruct( &ansiiTime, pTr->year, pTr->month, pTr->day );
    _time  = (DateToDayNumber( &ansiiTime) - CAL_DAYS_AT_1970) * 86400;

    _time += pTr->hour * 3600 + pTr->min * 60 + pTr->sec;

    return _time;
}

time_t RTC_TimeRecToTimeOffset ( TimeRec *pTr )
{
	time_t _time;

	_time = pTr->day * 86400 + pTr->hour * 3600ul + pTr->min * 60 + pTr->sec;

	return _time;
}

V RTC_TimeToTimeRec ( time_t time, TimeRec * pTr )
{
    struct tm ansiiTime;

    DayNumberToDate( CAL_DAYS_AT_1970 + (long)time/86400, &ansiiTime );

    pTr->year  = ansiiTime.tm_year;
    pTr->month = ansiiTime.tm_mon + 1;
    pTr->day   = ansiiTime.tm_mday;

    pTr->hour = (U8)((time % 86400) / 3600);
    pTr->min  = (U8)((time % 3600) / 60);
    pTr->sec  = (U8)(time % 60);

    pTr->ms   = 0;
}

#include <stdlib.h>
V RTC_TimeOffsetToTimeRec ( time_t tOffset, TimeRec * pTr )
{
	ldiv_t dt;
	pTr->year = 0;
	pTr->month = 0;
	dt = ldiv( (long)tOffset, 86400 );
	pTr->day = dt.quot > 255 ? 255 : dt.quot;
	dt = ldiv( dt.rem, 3600 );
	pTr->hour = dt.quot;
	dt = ldiv( dt.rem, 60 );
	pTr->min  = dt.quot;
	pTr->sec  = dt.rem;
	pTr->ms   = 0;
}

V RTC_TmStructToTimeRec ( struct tm *pTm, TimeRec *pTr )
{
    pTr->year    = pTm->tm_year + 1900;
    pTr->month   = pTm->tm_mon  + 1;
    pTr->day     = pTm->tm_mday;

    pTr->hour    = pTm->tm_hour;
    pTr->min     = pTm->tm_min;
    pTr->sec     = pTm->tm_sec;
    pTr->ms      = 0;
}

U32 RTC_TimeToFatTime ( time_t time)
{
    U32     res;
    TimeRec tr;

    RTC_TimeToTimeRec( time, &tr);

    res = (((U32) tr.year - 1980) << 25)
        |  ((U32) tr.month        << 21)
        |  ((U32) tr.day          << 16)
        |  ((U16) tr.hour         << 11)
        |  ((U16) tr.min          << 5)
        |  (      tr.sec          >> 1);

	return res;
}

V RTC_FatTimeToTimeRec ( U32 fatTime, TimeRec *pTr)
{
    pTr->year  = (fatTime >> 25) + 1980;
    pTr->month = (fatTime >> 21) & 15;
    pTr->day   = (fatTime >> 16) & 31;
    pTr->hour  = (fatTime >> 11) & 31;
    pTr->min   = (fatTime >>  5) & 63;
    pTr->sec   = (fatTime  & 31) << 1;
}

time_t RTC_FatTimeToTime ( U32 fatTime)
{
    TimeRec tr;

    tr.year   = (fatTime >> 25) + 1980;
    tr.month  = (fatTime >> 21) & 15;
    tr.day    = (fatTime >> 16) & 31;
    tr.hour   = (fatTime >> 11) & 31;
    tr.min    = (fatTime >>  5) & 63;
    tr.sec    = (fatTime  & 31) << 1;

    return RTC_TimeRecToTime( &tr);
}

/**
-----------------------------------------------------------------------------------------------------------------------------------
RTC and time Getters
*/

V RTC_GetRtc ( TimeRec * tr )
{
    ENTER_CRITICAL_REGION();
    *tr = rtc;
    LEAVE_CRITICAL_REGION();
}

/*
    Returns the day number since 1900/01/01 00:00:00.
        Expressed as a real number in day_No.fraction_of_day
*/
FP64 RTC_TimeNow_D_HMSsss ( V )
{
    struct tm ansiiTime;
    TimeRec tr;
    double timeNow_D_HMSsss;

    RTC_GetRtc( &tr);

    LoadDateStruct( &ansiiTime, tr.year, tr.month, tr.day);

    timeNow_D_HMSsss = (DateToDayNumber( &ansiiTime)+2 - CAL_DAYS_AT_1900) +
                       (tr.hour * 3600000.0 +  tr.min * 60000.0 + tr.sec*1000.0 + tr.ms) /
                       86400000.0;

    return timeNow_D_HMSsss;
}

/**
-----------------------------------------------------------------------------------------------------------------------------------
RTC string conversion functions

    All Return a pointer to a string with the following format
    YYYY/MM/DD hh:mm:ss.sss 23 Cs

Todo:
    1.  Make static string a TLS variable.
*/

PC RTC_TimeString ( RTC_TIMESTRING_OPTS tso )
{
    TimeRec tr;

    RTC_GetRtc( &tr );

    return RTC_MakeTimeStringTimeRec( tso, NULL, &tr);
}

PC RTC_TimeStringTime ( RTC_TIMESTRING_OPTS tso, time_t time )
{
    TimeRec tr;

    RTC_TimeToTimeRec( time, &tr );

    return RTC_MakeTimeStringTimeRec( tso, NULL, &tr );
}

PC RTC_TimeStringTmStruct ( RTC_TIMESTRING_OPTS tso, struct tm * pTm )
{
    TimeRec tr;

    RTC_TmStructToTimeRec( pTm, &tr );

    return RTC_MakeTimeStringTimeRec( tso, NULL, &tr );
}

PC RTC_MakeTimeString ( RTC_TIMESTRING_OPTS tso, RTC_TimeString_t *pTs )
{
    TimeRec tr;

    RTC_GetRtc( &tr );

    return RTC_MakeTimeStringTimeRec( tso, pTs, &tr );
}

PC RTC_MakeTimeStringTime ( RTC_TIMESTRING_OPTS tso, RTC_TimeString_t *pTs, time_t time )
{
    TimeRec tr;

#if 0
	if( (tso == TSO_UPTIME) || (tso == TSO_DDdhhmmss) )
	{
	}
	else
#endif
	RTC_TimeToTimeRec( time, &tr );

    return RTC_MakeTimeStringTimeRec( tso, pTs, &tr );
}

PC RTC_MakeTimeStringTmStruct ( RTC_TIMESTRING_OPTS tso, RTC_TimeString_t *pTs, struct tm * pTm )
{
    TimeRec tr;

    RTC_TmStructToTimeRec( pTm, &tr );

    return RTC_MakeTimeStringTimeRec( tso, pTs, &tr );
}

#include <stdio.h>
static RTC_TimeString_t ts;

PC RTC_MakeTimeStringTimeRec ( RTC_TIMESTRING_OPTS tso, RTC_TimeString_t * pTs, TimeRec *pTr )
{
    if( pTs == NULL )
        pTs = &ts;

    switch( tso ) {
		case TSO_hhmmss:
			sprintf( *pTs, "%.2u:%.2u:%.2u",
						pTr->hour, pTr->min, pTr->sec );
		break;
        case TSO_TIME:
            sprintf( *pTs, "%.2u:%.2u:%.2u.%.3u",
                        pTr->hour, pTr->min, pTr->sec,
                        pTr->ms );
        break;
        case TSO_DATE:
            sprintf( *pTs, "%.4u/%.2u/%.2u",
                        pTr->year , pTr->month, pTr->day );
        break;
        case TSO_YYYYMMDD_hhmm:
            sprintf( *pTs, "%.4u/%.2u/%.2u %.2u:%.2u",
                        pTr->year , pTr->month, pTr->day,
                        pTr->hour, pTr->min );
        break;
        case TSO_YYYYMMDD_hhmmss:
            sprintf( *pTs, "%.4u/%.2u/%.2u %.2u:%.2u:%.2u",
                        pTr->year , pTr->month, pTr->day,
                        pTr->hour, pTr->min, pTr->sec );
        break;
        case TSO_ALL:
            sprintf( *pTs, "%.4u/%.2u/%.2u %.2u:%.2u:%.2u.%.3u",
                        pTr->year , pTr->month, pTr->day,
                        pTr->hour, pTr->min, pTr->sec,
                        pTr->ms );
        break;
        case TSO_DDdhhmmss:
		case TSO_UPTIME:
		{
			PC pds = tso == TSO_UPTIME ? "" : "d ";

			U32 uptime;
			if( pTr )
				uptime = RTC_TimeRecToTime( pTr );
			else
				uptime = upTime;

			UI days = uptime / 86400u;
			uptime -= days * 86400u;
			UI hours = uptime / 3600u;
			uptime -= hours * 3600u;
			UI mins = uptime / 60u;
			uptime -= mins * 60u;
			UI secs = uptime;

			sprintf( *pTs, "%5u %s%.2u:%.2u:%.2u",
				days, pds, hours, mins, secs );
		}
        break;
        default:
            sprintf( *pTs, "Invalid RTC_TIMESTRING_OPTS %.2x", tso );
    }

    return *pTs;
}

PC RTC_MakeDurationString ( PC pStr, U32 ms )
{
	if( !pStr )
		pStr = ts;
	if( ms < 1000 )
		sprintf( pStr, "%u ms", ms );
	else if( ms < 10000 )
	{
		ms /= 10;
		sprintf( pStr, "%u.%.2u s", ms/100, ms%100 );
	}
	else if( ms < 60000 )
	{
		ms /= 100;
		sprintf( pStr, "%u.%u s", ms/10, ms%10 );
	}
	else if( ms < 3600000 )
	{
		ms /= 1000;
		sprintf( pStr, "%.2u:%.2u", ms/60, ms%60 );
	}
	else if( ms < 86400000 )
	{
		ms /= 1000;
		UI hours = ms / 3600u;
		ms -= hours * 3600u;
		UI mins = ms / 60u;
		ms -= mins * 60u;
		UI secs = ms;

		sprintf( pStr, "%.2u:%.2u:%.2u", hours, mins, secs );
	}
	else
	{
		ms /= 1000;
		UI days = ms / 86400u;
		ms -= days * 86400u;
		UI hours = ms / 3600u;
		ms -= hours * 3600u;
		UI mins = ms / 60u;
		ms -= mins * 60u;
		UI secs = ms;
		sprintf( pStr, "%5u d%.2u:%.2u:%.2u",
			days, hours, mins, secs );
	}

	return pStr;
}

/**
-----------------------------------------------------------------------------------------------------------------------------------
RTC Depricated functions
*/


/*
    2009/11/10 18:56:11.321 returns 20091110185611321
*/
S64 RTC_DateTime_BCD ( TimeRec * tr )
{
    return 10000000000000ull * tr->year + 100000000000ull * tr->month + 1000000000ull * tr->day +
                 10000000ul  * tr->hour +       100000ul  * tr->min   +       1000u   * tr->sec + tr->ms;
}

S64 RTC_DateTimeNow_BCD ( V )
{
    TimeRec tr;

    RTC_GetRtc( &tr);

    return RTC_DateTime_BCD( &tr );
}

/**
-----------------------------------------------------------------------------------------------------------------------------------
Utility functions
*/

extern U32 RTC_GetUpTime ( V )
{
    return upTime;
}

time_t RTC_GetTime ( V )
{
	return sysTime;
}


static inline UF8 _DaysInMonth ( UF8 m, UF16 y );

I RTC_DaysInMonth ( UF8 m, UF16 y )
{
    if( (m == 0) || (m > 12) || (y < 2000) )
        return -1;

    return _DaysInMonth( m, y );
}

B RTC_IsTimeRecValid ( const TimeRec *tr )
{
    struct tm ansiiTime;

    return	( LoadDateStruct( &ansiiTime, tr->year, tr->month, tr->day) == 0 ) &&
			( LoadTimeStruct( &ansiiTime, tr->hour, tr->min, tr->sec) == 0   );
}

/**
-----------------------------------------------------------------------------------------------------------------------------------
RTC and time setting functions
*/

V RTC_SetRtc( TimeRec * tr )
{
    time_t time;

    if( tr->year < 1900 )
        tr->year += 2000;

    time = RTC_TimeRecToTime( tr );

    ENTER_CRITICAL_REGION();
    sysTime	= time;
    tr->ms	= rtc.ms;
    rtc		= *tr;
    LEAVE_CRITICAL_REGION();
}

V RTC_SetTime( time_t time )
{
    TimeRec tr;

    if( time < SECONDS_BETWEEN_Y1970_Y2000 )
        time = SECONDS_BETWEEN_Y1970_Y2000;

    RTC_TimeToTimeRec( time, &tr );

    ENTER_CRITICAL_REGION();
    sysTime	= time;
    tr.ms	= rtc.ms;
    rtc		= tr;
    LEAVE_CRITICAL_REGION();
}


/**
-----------------------------------------------------------------------------------------------------------------------------------
Low level functions
*/

static const U8 daysInMonth[] = {
    0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};

static inline UF8 _DaysInMonth(  UF8 m, UF16 y )
{
    return  m != 2 ? daysInMonth[m] : daysInMonth[m] + ((y % 4) == 0);
}

V RTC_UpdateRtc ( V )
{
#if (TICKS_PER_SECOND == 1)
    /* Nothing	*/
#elif (TICKS_PER_SECOND == 1000)
    if( ++rtc.ms >= TICKS_PER_SECOND )
#elif (TICKS_PER_SECOND == 100 )
    if( (rtc.ms +=  10) >= (TICKS_PER_SECOND*10) )
#elif (TICKS_PER_SECOND == 10)
    if( (rtc.ms += 100) >= (TICKS_PER_SECOND*100) )
#else
    #error "System ticks per second must be 1, 10, 100 or 1000"
#endif
    { /* Every Second */
        ++upTime;
        ++sysTime;
#if (TICKS_PER_SECOND > 1)
        rtc.ms = 0;
#endif
        if( ++rtc.sec >= 60 )
        {
            rtc.sec = 0;
            if( ++rtc.min >= 60 )
            {
                rtc.min = 0;
                if( ++rtc.hour >= 24 )
                {
                    rtc.hour = 0;
                    if( ++rtc.day > _DaysInMonth(rtc.month, rtc.year) )
                    {
                        rtc.day = 1;
                        if( ++rtc.month > 12 )
                        {
                            rtc.month = 1;
                            rtc.year++;
                        }
                    }
                }
            }
        }
    }
}

/**
-----------------------------------------------------------------------------------------------------------------------------------
RTL replacement functions
*/

#if 0
/*
    Returns the number of seconds since 1970/01/01 00:00:00
*/
__time32_t __time32 ( __time32_t *t )
{
    __time32_t _time = (__time32_t)sysTime;
    if( t != NULL)
        *t = _time;
    return _time;
}

/*
 * The "clock" function should return the processor time used by the
 * program from some implementation-defined start time.  The value
 * should be such that if divided by the macro CLOCKS_PER_SEC the
 * result should yield the time in seconds.
*/
#include <OsUtils/OsAbstraction.h>
clock_t clock ( V )
{
    return  Osa_TicksGet();
}
#endif
