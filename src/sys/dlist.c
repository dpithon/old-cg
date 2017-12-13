#include "dlist.h"


static void *dlist_iter(struct iterator *iter)
{
	void *cursor = DLIST_ITERATOR(iter)->cursor;
	if (cursor)
		DLIST_ITERATOR(iter)->cursor = 
			DLIST_ITERATOR(iter)->cursor->next;
	return cursor;
}


void init_dlist_iterator(struct dlist_iterator *iter, struct dlist *dlist)
{
	iterator(ITERATOR(iter), dlist_iter, dlist_iter, 0);
	iter->cursor = dlist->head;
}


void _dlist_append(struct dlist *dlist, struct dlink *dlink)
{

	dlink->next = 0;
	dlink->prev = dlist->tail;

	if (!dlist->head) {
		dlist->head = dlist->tail = dlink;
	} else {
		dlist->tail->next = dlink;
		dlist->tail = dlink;
	}
}
