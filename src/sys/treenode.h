#ifndef TREENODE_H
#define TREENODE_H

#include <assert.h>


struct treenode {
	struct treenode *parent;
	struct treenode *left_child;
	struct treenode *right_child;
};


#define TREENODE(i)	((struct treenode*)i)
#define treenode_parent(i) 	_treenode_parent(TREENODE(i))
#define treenode_left_child(i)	_treenode_left_child(TREENODE(i))
#define treenode_right_child(i)	_treenode_right_child(TREENODE(i))

static inline struct treenode *_treenode_parent(struct treenode *treenode)
{
	assert(treenode != 0);
	return treenode->parent;
}

static inline struct treenode *_treenode_left_child(struct treenode *treenode)
{
	assert(treenode != 0);
	return treenode->left_child;
}


static inline struct treenode *_treenode_right_child(struct treenode *treenode)
{
	assert(treenode != 0);
	return treenode->right_child;
}

#endif /* TREENODE_H */
