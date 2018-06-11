/*
 * Tristan Hilbert
 * 6/10/18
 * AVL Binary Tree implementation
 *
 */

#include "binary_tree.h"

struct avl_link {
   TYPE data;
   int height;
   struct avl_link* left;
   struct avl_link* right;
};

struct bin_tree{
   struct avl_link * head;
   int size;
};

void init_tree(struct bin_tree* tree){}
void add_tree(struct bin_tree* tree, TYPE e){}
void remove_tree(struct bin_tree* tree, TYPE e){}
TYPE get_min(struct bin_tree* tree){}
TYPE get_max(struct bin_tree* tree){}
void print_tree(struct bin_tree* tree){}
void del_tree(struct bin_tree* tree){}
