#ifndef ITERATOR_H
#define ITERATOR_H

#define CAST_ITERATOR(i) 	((struct iterator*)(i))
#define foreach(T, s, iter)	for (s = (iter_init(iter, T));\
				     s;\
				     s = (iterate(iter, T)))

struct iterator {
	void *(*init)(struct iterator*);
	void *(*next_item)(struct iterator*);
	void (*cleanup)(struct iterator*);
};


static inline void iterator(struct iterator *iter, 
			    void *(*init)(struct iterator*),
			    void *(*next_item)(struct iterator*),
			    void (*cleanup)(struct iterator*))
{
	iter->init = init;
	iter->next_item = next_item;
	iter->cleanup = cleanup;
}


#define iter_init(i, TYPE) CAST_ ## TYPE(_iter_init(CAST_ITERATOR(i)))
static inline void *_iter_init(struct iterator *iter)
{
	return iter->init(iter);
}


#define iterate(i,TYPE) CAST_ ## TYPE(_iterate(CAST_ITERATOR(i)))
static inline void *_iterate(struct iterator *iter)
{
	void *node = iter->next_item(iter);
	if (node == 0 && iter->cleanup) 
		iter->cleanup(iter);
	return node;
}

#endif /* ITERATOR_H */
