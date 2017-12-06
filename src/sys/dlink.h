#ifndef DLINK_H
#define DLINK_H

#include <assert.h>


struct dlink {
	struct dlink *prev;
	struct dlink *next;
};


#define CAST_DLINK(i)	((struct dlink*)i)
#define dlink_next(i) 	dlink__next(CAST_DLINK(i))
#define dlink_prev(i)	dlink__prev(CAST_DLINK(i))


static inline struct dlink *dlink__next(struct dlink *dlink)
{
	assert(dlink != 0);
	return dlink->next;
}


static inline struct dlink *dlink__prev(struct dlink *dlink)
{
	assert(dlink != 0);
	return dlink->prev;
}

#endif /* DLINK_H */
