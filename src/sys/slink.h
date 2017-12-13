#ifndef SLINK_H
#define SLINK_H

#include <assert.h>


struct slink {
	struct slink *next;
};


#define CAST_SLINK(i)		((struct slink*)i)
#define slink_next(i)		slink__next(CAST_SLINK(i))
#define slink_is_last(i)	slink__is_last(CAST_SLINK(i))


static inline int slink__is_last(struct slink *slink)
{
	assert(slink != 0);
	return slink->next == 0;
}


static inline struct slink *slink__next(struct slink *slink)
{
	assert(slink != 0);
	return slink->next;
}


#endif /* SLINK_H */
