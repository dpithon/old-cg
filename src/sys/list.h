#ifndef LIST_H
#define LIST_H

#include "iterator.h"
#include "dlink.h"

#define CAST_LIST_ITERATOR(i) ((struct list_iterator*)i)
#define CAST_LIST(l) ((struct list*)l)

#define list_append(l, d) _list_append(CAST_LIST(l), CAST_DLINK(d))

struct list {
	struct dlink *head;
	struct dlink *tail;
};


struct list_iterator {
	struct iterator iter;
	struct dlink *cursor;
};


extern void init_list_iterator(struct list_iterator*, struct list*);
extern void _list_append(struct list*, struct dlink*);

#endif /* LIST_H */
