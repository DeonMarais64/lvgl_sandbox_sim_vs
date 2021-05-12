#ifndef DATELIB_H
#define DATELIB_H
/*--------------------------------------------------------------
 * Prototypes for datelib.c
 *-------------------------------------------------------------*/

#include <time.h>

extern long    DateDiff			( struct tm *, struct tm * );
extern long    DateToDayNumber	( struct tm * );
extern int     DayNumberToDate	( long int, struct tm * );
extern int     DayOfWeek		( struct tm * );
extern int     DayOfYear		( struct tm * );
extern int     IsDateValid		( struct tm * );
extern int     IsTimeValid		( struct tm * );
extern int     IsYearLeap		( int );
extern int     LoadDateStruct	( struct tm *, int, int, int );
extern int     LoadTimeStruct	( struct tm *, int, int, int );
extern double  TimeDiff			( struct tm *, struct tm * );
extern int     TimeSprintf		( char *, int, char *, struct tm * );

#ifndef YES
#define YES     1
#define NO      0
#endif


#endif /* DATELIB_H */
