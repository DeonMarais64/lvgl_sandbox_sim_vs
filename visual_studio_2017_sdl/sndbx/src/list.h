
/**
 *	list.h
 *	Copyright (c) 2010 TJ Holowaychuk <tj@vision-media.ca>
 *	https://github.com/clibs/list#list
 *
 *	Node prototypes.
 *		list_node_t *list_node_new( void *val );
 *
 *	list_t prototypes.
 *		list_t		*list_new(void);
 *		list_node_t *list_rpush(list_t *self, list_node_t *node);
 *		list_node_t *list_lpush(list_t *self, list_node_t *node);
 *		list_node_t *list_find(list_t *self, void *val);
 *		list_node_t *list_at(list_t *self, int index);
 *		list_node_t *list_rpop(list_t *self);
 *		list_node_t *list_lpop(list_t *self);
 *		void		list_remove(list_t *self, list_node_t *node);
 *		void		list_destroy(list_t *self);
 *
 *	list_t iterator prototypes.
 *		list_iterator_t *list_iterator_new(list_t *list, list_direction_t direction);
 *		list_iterator_t *list_iterator_new_from_node(list_node_t *node, list_direction_t direction);
 *		list_node_t		*list_iterator_next(list_iterator_t *self);
 *		void			list_iterator_destroy(list_iterator_t *self);
 *
 */

#ifndef LIST_H
#define LIST_H

#include "list_conf.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !LIST_MEM_CUSTOM
#include <stdlib.h>
#endif

/* Library version */

#define LIST_VERSION "0.0.5"

/* Memory management macros */


#ifndef LIST_MALLOC
#define LIST_MALLOC malloc
#endif

#ifndef LIST_FREE
#define LIST_FREE free
#endif

/*
 * list_t node struct.
 */
typedef struct list_node {
  struct list_node *prev;
  struct list_node *next;
  void *val;
} list_node_t;

/** Node prototypes. */
list_node_t *
list_node_new( void *val );

/*
 * list_t struct.
 */
typedef struct {
  list_node_t *head;
  list_node_t *tail;
  unsigned int len;
#if !LIST_VAL_NO_FREE
  void (*free)(void *val);
#endif
#if !LIST_VAL_NO_MATCH
  int (*match)(void *a, void *b);
#endif
} list_t;


/** list_t prototypes. */
list_t *
list_new(void);

list_node_t *
list_rpush(list_t *self, list_node_t *node);

list_node_t *
list_lpush(list_t *self, list_node_t *node);

list_node_t *
list_find(list_t *self, void *val);

list_node_t *
list_at(list_t *self, int index);

list_node_t *
list_rpop(list_t *self);

list_node_t *
list_lpop(list_t *self);

void
list_remove(list_t *self, list_node_t *node);

void
list_destroy(list_t *self);

/* Deon Extentions */
list_t *
list_init(list_t *self);

list_t *
list_del( list_t *self );

list_t *
list_rclean(list_t *self);

list_t *
list_lclean( list_t *self );

/*
 * list_t iterator direction.
 */
typedef enum
{
	LIST_HEAD,
	LIST_TAIL,
} list_direction_t;

/*
 * list_t iterator struct.
 */
typedef struct
{
	list_node_t *next;
	list_direction_t direction;
} list_iterator_t;

/** list_t iterator prototypes. */
list_iterator_t *
list_iterator_new(list_t *list, list_direction_t direction);

list_iterator_t *
list_iterator_new_from_node(list_node_t *node, list_direction_t direction);

list_node_t *
list_iterator_next(list_iterator_t *self);

void
list_iterator_destroy(list_iterator_t *self);

/*Deon Extentions */
list_iterator_t *
list_iterator_init( list_iterator_t *self, list_t *list, list_direction_t direction );
list_iterator_t *
list_iterator_init_from_node( list_iterator_t *self, list_node_t *node, list_direction_t direction );

#ifdef __cplusplus
}
#endif

#endif /* LIST_H */
