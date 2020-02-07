#ifndef SNDBX_NAV_H
#define SNDBX_NAV_H

extern void sndbx_nav_init	( void );
extern void sndbx_nav_clean	( void );
extern void sndbx_nav_cleanup ( void );

extern void sndbx_nav_page_push( const void * page );
extern void sndbx_nav_page_branch( const void * branch, const void * page );
extern const void * sndbx_nav_page_get_prev( const void * page );
extern const void * sndbx_nav_page_get_next( const void * page );
extern const void * sndbx_nav_page_get_prev_next( const void * page, const void ** pprev, const void ** pnext );

extern void sndbx_nav_dump_list( void );

extern void sndbx_nav_test( void );


#endif /*SNDBX_NAV_H*/

