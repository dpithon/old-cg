#ifndef DLIST_H
#define DLIST_H

#include "iterator.h"
#include "dlink.h"

#define DLIST_ITERATOR(i) ((struct dlist_iterator*)i)
#define DLIST(l) ((struct dlist*)l)

#define dlist_append(l, d) _dlist_append(DLIST(l), DLINK(d))

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
