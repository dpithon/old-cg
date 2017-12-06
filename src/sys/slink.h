#ifndef SLINK_H
#define SLINK_H

#include <assert.h>


struct slink {
	struct slink *next;
};


#define CAST_SLINK(i)	((struct slink*)i)
#define slink_next(i) 	slink__next(CAST_SLINK(i))


static inline struct slink *slink__next(struct slink *slink)
{
	assert(slink != 0);
	return slink->next;
}


#endif /* SLINK_H */
