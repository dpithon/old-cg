#ifndef SLIST_H
#define SLIST_H

#include "iterator.h"
#include "slink.h"

#define CAST_SLIST_ITERATOR(i) ((struct slist_iterator*)i)
#define CAST_SLIST(l) ((struct slist*)l)

#define slist_append(l, d) _slist_append(CAST_SLIST(l), CAST_SLINK(d))

struct slist {
	struct slink *head;
	struct slink *tail;
};


struct slist_iterator {
	struct iterator iter;
	struct slink *cursor;
};


extern void init_slist_iterator(struct slist_iterator*, struct slist*);
extern void _slist_append(struct slist*, struct slink*);

#endif /* SLIST_H */
