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

struct bin_tree;

void init_tree(struct bin_tree*);
void add_tree(struct bin_tree*, TYPE);
void remove_tree(struct bin_tree*, TYPE);
TYPE get_min(struct bin_tree*);
TYPE get_max(struct bin_tree*);
void print_tree(struct bin_tree*);
void del_tree(struct bin_tree*);

#endif
