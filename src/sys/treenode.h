#ifndef TREENODE_H
#define TREENODE_H

#include <assert.h>


struct treenode {
	struct treenode *parent;
	struct treenode *left_child;
	struct treenode *right_child;
};


#define TREENODE(i)	((struct treenode*)i)
#define treenode_parent(i) 	treenode__parent(TREENODE(i))
#define treenode_left_child(i)	treenode__left_child(TREENODE(i))
#define treenode_right_child(i)	treenode__right_child(TREENODE(i))

static inline struct treenode *treenode__parent(struct treenode *treenode)
{
	assert(treenode != 0);
	return treenode->parent;
}

static inline struct treenode *treenode__left_child(struct treenode *treenode)
{
	assert(treenode != 0);
	return treenode->left_child;
}


static inline struct treenode *treenode__right_child(struct treenode *treenode)
{
	assert(treenode != 0);
	return treenode->right_child;
}

#endif /* TREENODE_H */
