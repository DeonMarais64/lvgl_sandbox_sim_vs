/*
 * Todo: Re-Impliment using lv_ll
 */
#include "sndbx_nav.h"
#include "list.h"

static list_t nav;

void sndbx_nav_init ( void )
{
#if 1	
	sndbx_nav_cleanup();		/*Make sure list is free*/
#else
//	list_init( &nav );	/* Unnecesary, Should already be correct at startup */
#endif
}

void sndbx_nav_clean ( void )
{
	list_rclean( &nav );
}

void sndbx_nav_cleanup ( void )
{
	list_del( &nav );
}

static list_node_t * page_node_get( const void * page )
{	
	return list_find( &nav, (void*)page );
}

static void page_remove_after( const void * page )
{
	list_node_t * node = page_node_get( page );
	if( !node )
		return;
	node = node->next;
	if( !node )
		return;

	list_iterator_t _it, *it = &_it;
	list_iterator_init_from_node( it, node, LIST_HEAD );
	while( (node = list_iterator_next( it )) )
		list_remove( &nav, node );
}

void sndbx_nav_page_push( const void * page )
{
	list_node_t * node = page_node_get( page );
	if( !node )
		list_rpush( &nav, list_node_new( (void *)page ) );
}

void sndbx_nav_page_branch( const void * branch, const void * page )
{
	list_node_t * node = page_node_get( page );
	if( !node )
	{
		page_remove_after( branch );
		list_rpush( &nav, list_node_new( (void *)page ) );
	}
}

const void * sndbx_nav_page_get_prev( const void * page )
{
	list_node_t *node = page_node_get( page );
	if( !node )	return NULL;

	list_iterator_t _it, *it = &_it;
	list_iterator_init_from_node( it, node, LIST_HEAD );
	node = list_iterator_next( it );

	if( !node )	return NULL;
	return node->prev ? node->prev->val : NULL;
}

const void * sndbx_nav_page_get_next( const void * page )
{
	list_node_t *node = page_node_get( page );
	if( !node )	return NULL;

	list_iterator_t _it, *it = &_it;
	list_iterator_init_from_node( it, node, LIST_HEAD );
	node = list_iterator_next( it );

	if( !node )	return NULL;
	return node->next ? node->next->val : NULL;
}

const void * sndbx_nav_page_get_prev_next( const void * page, const void ** pprev, const void ** pnext )
{
	list_node_t *node = page_node_get( page );
	if( !node )	return NULL;

	list_iterator_t _it, *it = &_it;
	list_iterator_init_from_node( it, node, LIST_HEAD );
	node = list_iterator_next( it );
	if( !node )	return NULL;

	if( pprev )
		*pprev = node->prev ? node->prev->val : NULL;
	if( pnext )
		*pnext = node->next ? node->next->val : NULL;
	return page;
}

#define NAV_INCLUDE_TEST 1
#if NAV_INCLUDE_TEST

#include <stdio.h>
#include <string.h>

#define OUTPUT(x) ((x)?(x):"None")

static void dump_pages( const void * from )
{
	const char * frm = (const char *)from;
#if 1
	const void * prv=NULL;
	const void * nxt=NULL;
	sndbx_nav_page_get_prev_next( from, &prv, &nxt );
#else
	const char * prv = (const char *)sndbx_nav_page_get_prev( from );
	const char * nxt = (const char *)sndbx_nav_page_get_next( from );
#endif

	printf(
		"From %s,\n"
		"  Previous : %s\n"
		"      Next : %s\n"
		, OUTPUT(frm)
		, OUTPUT(prv)
		, OUTPUT(nxt)
	);
}

static void dump_list( list_t * list, list_direction_t direction )
{
	list_iterator_t it;
	list_node_t *p_node;

	puts(
		direction == LIST_HEAD ? "\nList from head" :
		direction == LIST_TAIL ? "\nList from tail" :
		"\n?? List direction"
	);
	list_iterator_init( &it, list, direction );
	while( (p_node = list_iterator_next( &it )) )
		printf( "    %s\n", (char*)p_node->val );
}

static void dump_list_hex( list_t * list, list_direction_t direction )
{
	list_iterator_t it;
	list_node_t *p_node;

	puts(
		direction == LIST_HEAD ? "\nNav list from head" :
		direction == LIST_TAIL ? "\nNav list from tail" :
		"\n?? Nav list direction"
	);
	list_iterator_init( &it, list, direction );
	while( (p_node = list_iterator_next( &it )) )
		printf( "    %p\n", p_node->val );
}

void sndbx_nav_dump_list( void )
{
	dump_list_hex( &nav, LIST_HEAD );
}

void sndbx_nav_test( void )
{
	printf( "\nNav Test ..\n" );
	sndbx_nav_init();
	sndbx_nav_page_push( "Home" );

	sndbx_nav_page_push( "Info" );
	sndbx_nav_page_push( "Diagnostics" );

	dump_list( &nav, LIST_HEAD );

	dump_pages( "Home" );
	dump_pages( "Info" );
	dump_pages( "Diagnostics" );

	sndbx_nav_clean();

	sndbx_nav_page_push( "Settings" );
	sndbx_nav_page_push( "Calibration" );
	sndbx_nav_page_push( "Load Cell" );

	dump_list( &nav, LIST_HEAD );

	dump_pages( "Home" );
	dump_pages( "Settings" );
	dump_pages( "Calibration" );
	dump_pages( "Load Cell" );

	sndbx_nav_page_push( "Calibration" );
	sndbx_nav_page_push( "Displacement" );

	dump_list( &nav, LIST_HEAD );

	dump_pages( "Home" );
	dump_pages( "Settings" );
	dump_pages( "Calibration" );
//	dump_pages( "Displacement" );

	sndbx_nav_cleanup();
	dump_list( &nav, LIST_HEAD );

	printf( "\nNav Test Done.\n\n" );
}
#endif

