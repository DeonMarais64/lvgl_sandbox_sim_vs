#ifndef LIST_CONF_H
#define LIST_CONF_H

#if 1

#define LIST_VAL_NO_FREE	1
#define LIST_VAL_NO_MATCH	1
#define LIST_MEM_CUSTOM		1
#define LIST_DEON_MODS		1


#if LIST_MEM_CUSTOM
#ifndef LV_MEM_H
#include <stdlib.h>
#include <stdint.h>
extern void * lv_mem_alloc( uint32_t size );
extern void lv_mem_free( void * );

#define LIST_MALLOC lv_mem_alloc
#define LIST_FREE lv_mem_free
#endif

#endif


#endif /* 1 */
#endif /*!LIST_CONF_H */
