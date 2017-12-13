#include "slist.h"


static void *slist_iter(struct iterator *iter)
{
	void *cursor = SLIST_ITERATOR(iter)->cursor;
	if (cursor)
		SLIST_ITERATOR(iter)->cursor = 
			SLIST_ITERATOR(iter)->cursor->next;
	return cursor;
}


void init_slist_iterator(struct slist_iterator *iter, struct slist *slist)
{
	iterator(ITERATOR(iter), slist_iter, slist_iter, 0);
	iter->cursor = slist->head;
}


void _slist_append(struct slist *slist, struct slink *slink)
{

	slink->next = 0;

	if (!slist->head) {
		slist->head = slist->tail = slink;
	} else {
		slist->tail->next = slink;
		slist->tail = slink;
	}
}
