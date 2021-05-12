
//
// list.c
//
// Copyright (c) 2010 TJ Holowaychuk <tj@vision-media.ca>
//

#include "list.h"

/*
 * Allocate a new list_t. NULL on failure.
 */
list_t *
list_new(void) {
  list_t *self;
  if (!(self = LIST_MALLOC(sizeof(list_t))))
    return NULL;
  self->head = NULL;
  self->tail = NULL;
  self->len = 0;
#if !LIST_VAL_NO_FREE
  self->free = NULL;
#endif
#if !LIST_VAL_NO_MATCH
  self->match = NULL;
#endif
  return self;
}

/*
 * Free the list.
 */
void
list_destroy(list_t *self) {
  unsigned int len = self->len;
  list_node_t *next;
  list_node_t *curr = self->head;

  while (len--) {
    next = curr->next;
#if !LIST_VAL_NO_FREE
	if (self->free) self->free(curr->val);
#endif
    LIST_FREE(curr);
    curr = next;
  }

  LIST_FREE(self);
}

/* Append, Right */

/*
 * Append the given node to the list
 * and return the node, NULL on failure.
 */
list_node_t *
list_rpush(list_t *self, list_node_t *node) {
  if (!node) return NULL;

  if (self->len) {
    node->prev = self->tail;
    node->next = NULL;
    self->tail->next = node;
    self->tail = node;
  } else {
    self->head = self->tail = node;
    node->prev = node->next = NULL;
  }

  ++self->len;
  return node;
}

/*
 * Return / detach the last node in the list, or NULL.
 */
list_node_t *
list_rpop(list_t *self) {
  if (!self->len) return NULL;

  list_node_t *node = self->tail;

  if (--self->len) {
    (self->tail = node->prev)->next = NULL;
  } else {
    self->tail = self->head = NULL;
  }

  node->next = node->prev = NULL;
  return node;
}

/* Prepend, Left */
/*
 * Prepend the given node to the list
 * and return the node, NULL on failure.
 */
list_node_t *
list_lpush( list_t *self, list_node_t *node )
{
	if( !node ) return NULL;

	if( self->len )
	{
		node->next = self->head;
		node->prev = NULL;
		self->head->prev = node;
		self->head = node;
	}
	else
	{
		self->head = self->tail = node;
		node->prev = node->next = NULL;
	}

	++self->len;
	return node;
}

/*
 * Return / detach the first node in the list, or NULL.
 */
list_node_t *
list_lpop(list_t *self) {
  if (!self->len) return NULL;

  list_node_t *node = self->head;

  if (--self->len) {
    (self->head = node->next)->prev = NULL;
  } else {
    self->head = self->tail = NULL;
  }

  node->next = node->prev = NULL;
  return node;
}


/*
 * Return the node associated to val or NULL.
 */
list_node_t *
list_find(list_t *self, void *val) {
#if	!LIST_DEON_MODS
	list_iterator_t *it = list_iterator_new( self, LIST_HEAD );
	list_node_t *node;

	while( (node = list_iterator_next(it)) ) {
#if !LIST_VAL_NO_MATCH
		if( self->match ) {
			if( self->match(val, node->val) ) {
				list_iterator_destroy( it );
				return node;
			}
		} else
#endif
		if( val == node->val ) {
			list_iterator_destroy( it );
			return node;
		}
	}

	list_iterator_destroy( it );
	return NULL;
#else /* Make iterator an auto variable */
	list_iterator_t _it, *it = &_it;
	list_iterator_init( it, self, LIST_HEAD );
	list_node_t *node;

	while( (node = list_iterator_next(it)) ) {
#if !LIST_VAL_NO_MATCH
		if( self->match ) {
			if( self->match(val, node->val) )
				return node;
		} else
#endif
		if( val == node->val )
			return node;
	}

	return NULL;
#endif
}

/*
 * Return the node at the given index or NULL.
 */
list_node_t *
list_at(list_t *self, int index) {
  list_direction_t direction = LIST_HEAD;

  if (index < 0) {
    direction = LIST_TAIL;
    index = ~index;
  }

  if ((unsigned)index < self->len) {
#if	!LIST_DEON_MODS
	  list_iterator_t *it = list_iterator_new( self, direction );
	  list_node_t *node = list_iterator_next( it );
	  while( index-- ) node = list_iterator_next( it );
	  list_iterator_destroy( it );
	  return node;
#else /* Make iterator an auto variable */
	  list_iterator_t _it, *it = &_it;
	  list_iterator_init( it, self, direction );
	  list_node_t *node = list_iterator_next( it );
	  while( node && index-- ) node = list_iterator_next( it );
	  return node;
#endif
  }

  return NULL;
}

/*
 * Remove the given node from the list, freeing it and it's value.
 */
void
list_remove(list_t *self, list_node_t *node) {
  node->prev
    ? (node->prev->next = node->next)
    : (self->head = node->next);

  node->next
    ? (node->next->prev = node->prev)
    : (self->tail = node->prev);

#if !LIST_VAL_NO_FREE
  if (self->free) self->free(node->val);
#endif

  LIST_FREE(node);
  --self->len;
}

/* Deon, Extentions */
/*
 * Initialises a list
 * if enabled and required, 
 *     free and/or match need to be set afterward.
 */
list_t *
list_init(list_t *self)
{
	if( !self )
		return NULL;
	self->head = NULL;
	self->tail = NULL;
	self->len = 0;
#if !LIST_VAL_NO_FREE
	self->free = NULL;
#endif
#if !LIST_VAL_NO_MATCH
	self->match = NULL;
#endif
	return self;
}

#if 1
/*
 * Deletes all contents of a list.
 * Does not delete the list itself
 */
list_t *
list_del( list_t *self )
{
	if( !self )
		return NULL;

	unsigned int len = self->len;
	list_node_t *next;
	list_node_t *curr = self->head;

	while( len-- )
	{
		next = curr->next;
#if !LIST_VAL_NO_FREE
		if( self->free ) self->free( curr->val );
#endif
		LIST_FREE( curr );
		curr = next;
	}

	self->head = NULL;
	self->tail = NULL;
	self->len = 0;

	return self;
}

/*
 * Deletes all children of a list
 * I.E, deletes all but the root node
 */
list_t *
list_rclean( list_t *self )
{	
	if( !self )
		return NULL;

	while( self->len > 1 )
		list_remove( self, self->tail );

	return self;
}

/*
 * Deletes all children of a list
 * I.E, deletes all but the root node
 */
list_t *
list_lclean( list_t *self )
{
	if( !self )
		return NULL;

	while( self->len > 1 )
		list_remove( self, self->head );

	return self;
}

#endif


