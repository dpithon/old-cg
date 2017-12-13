#ifndef DLINK_H
#define DLINK_H

#include <assert.h>


struct dlink {
	struct dlink *prev;
	struct dlink *next;
};


#define DLINK(i)		((struct dlink*)i)
#define dlink_next(i)		dlink__next(DLINK(i))
#define dlink_prev(i)		dlink__prev(DLINK(i))
#define dlink_is_first(i)	dlink__is_first(DLINK(i))
#define dlink_is_last(i)	dlink__is_last(DLINK(i))


static inline int dlink__is_first(struct dlink *dlink)
{
	assert(dlink != 0);
	return dlink->prev == 0;
}


static inline int dlink__is_last(struct dlink *dlink)
{
	assert(dlink != 0);
	return dlink->next == 0;
}


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
