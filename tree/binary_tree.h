/*
 * Tristan Hilbert
 * 6/10/18
 * Binary Tree Header File
 *
 */

#ifndef __BINARY_TREE_H
#define __BINARY_TREE_H

#ifndef TYPE
#define TYPE int
#endif

#ifndef LT
#define LT(A, B) (A < B)
#endif

#ifndef EQ
#define EQ(A, B) (A == B)
#endif

struct avl_link;
struct bin_tree{
   struct avl_link * head;
   int size;
};

void init_tree(struct bin_tree*);
void add_tree(struct bin_tree*, TYPE);
void remove_tree(struct bin_tree*, TYPE);
TYPE get_min(struct bin_tree*);
TYPE get_max(struct bin_tree*);
void print_tree(struct bin_tree*);
void del_tree(struct bin_tree*);
int IS_AVL(struct bin_tree*);
int IS_BIN_TREE(struct bin_tree*);

#endif
