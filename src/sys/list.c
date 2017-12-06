#include "list.h"


static void *list_iter(struct iterator *iter)
{
	void *cursor = CAST_LIST_ITERATOR(iter)->cursor;
	if (cursor)
		CAST_LIST_ITERATOR(iter)->cursor = 
			CAST_LIST_ITERATOR(iter)->cursor->next;
	return cursor;
}


void init_list_iterator(struct list_iterator *iter, struct list *list)
{
	iterator(CAST_ITERATOR(iter), list_iter, list_iter, 0);
	iter->cursor = list->head;
}


void _list_append(struct list *list, struct dlink *dlink)
{

	dlink->next = 0;

	if (!list->head) {
		list->head = list->tail = dlink;
	} else {
		list->tail->next = dlink;
		list->tail = dlink;
	}
}
