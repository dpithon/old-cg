#ifndef DLIST_H
#define DLIST_H

#include "iterator.h"
#include "dlink.h"

#define CAST_DLIST_ITERATOR(i) ((struct dlist_iterator*)i)
#define CAST_DLIST(l) ((struct dlist*)l)

#define dlist_append(l, d) _dlist_append(CAST_DLIST(l), CAST_DLINK(d))

struct dlist {
	struct dlink *head;
	struct dlink *tail;
};


struct dlist_iterator {
	struct iterator iter;
	struct dlink *cursor;
};


extern void init_dlist_iterator(struct dlist_iterator*, struct dlist*);
extern void _dlist_append(struct dlist*, struct dlink*);

#endif /* DLIST_H */
