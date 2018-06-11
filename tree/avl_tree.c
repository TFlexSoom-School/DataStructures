/*
 * Tristan Hilbert
 * 6/10/18
 * AVL Binary Tree implementation
 *
 */

#include "binary_tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* Struct Definitions */
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

/* Struct Definitions END */

/******************************************/

/* Function Prototypes */

void _setHeight(struct avl_link*);
struct avl_link * _balance(struct avl_link *);


/* End Function Prototypes */

/* Function Definitions * ******************************/

/* Initialize Tree with default values
 * Fails assertion check if pointer is not NULL */
void init_tree(struct bin_tree* tree){
   assert(tree);
   tree->head = NULL;
   assert(tree->head);
   tree->size = 0;
}

/* 
 * add_tree(bin_tree, e)
 * adds an element to the tree
 * param: pointer to the tree and data value
 * post: New memory will be create for tree
 * error: if no memory can be allocated -> failed Assertion
 */
struct avl_link * _add_node_r(struct avl_link*, TYPE);
void add_tree(struct bin_tree* tree, TYPE e){
   assert(tree);
   tree->head =_add_node_r(tree->head, e);
   tree->size ++;

}

/* Recursive call to the above function */
struct avl_link * _add_node_r(struct avl_link* node, TYPE e){
   if(node){
      if(LT(e, node->data)){
         node->left = _add_node_r(node->left, e);
	 node->left = _balance(node->left);
      }else
	 node->right = _add_node_r(node->right, e);
         node->right = _balance(node->right);
   }else{
      return malloc(sizeof(struct avl_link*));
   }
}

/*
 * remove_tree(bin_tree, e)
 * removes an element from the tree if it exists
 * param pointer to the tree and data value
 * post: entity will be freed from tree if existant
 */
struct avl_link * remove_tree_r(struct avl_link*, TYPE);
struct avl_link *_new_data_remove(struct avl_link* node);
void remove_tree(struct bin_tree* tree, TYPE e){
   assert(tree);
   tree->head = remove_tree_r(tree->head, e);
   tree->size --;
}

/* Recursive call to funtion above */
struct avl_link * remove_tree_r(struct avl_link* node, TYPE e){
   if(node){
      if(EQ(node->data, e)){
         return _new_data_remove(node);
      }else if(LT(e, node->data)){
         remove_tree_r(node->left);
      }else{
         remove_tree_r(node->right);
      }
      return _balance(node);
   }
}

/* Assigns the right most data to the node or removes the node entirely */
struct avl_link*  _new_data_remove(struct avl_link* node){
   struct avl_link * it;
   TYPE temp;
   if(node->right){
      
      it = node->right;
      if(it->left == NULL){
        temp = it->data;
	free(node->right);
	node->right = NULL;
	node->data = temp;
	return node;
      }

      while(it->left->left){
         it = it->left;
      }
      temp = it->left->data;
      free(it->left);
      it->left = NULL;
      node->data = temp;
      return node;
   
   }else{
      it = node->left;
      free(node);
      return it;
   }
}

/* Returns minimum most value of the tree */
TYPE get_min(struct bin_tree* tree){
   struct avl_link * it;
   assert(tree);
   it = tree->head;
   while(it->left){
      it = it->left;
   }
   return it->data;
}

/* Returns the maximum most value of the tree */
TYPE get_max(struct bin_tree* tree){
   struct avl_link * it;
   assert(tree);
   it = tree->head;
   while(it->right){
      it = it->right;
   }
   return it->data;
}

/* Prints Breadth of Tree */
void print_tree(struct bin_tree* tree){
   struct avl_link ** array;
   int arr_size = 0, i = 0;
   assert(tree);
   array = malloc(sizeof(struct avl_link*) * (tree->size << 1));
   assert (array);
   array[arr_size ++] = tree->head;
   while(i < arr_size){
      printf("Node %d: %d |", i, array[i]->data); /* Should be %d %g not %d %d */
      if(array[i]){
         array[arr_size ++] = array[i]->left;
	 array[arr_size ++] = array[i]->right;
      }

      if(i % (i >> 1) == 0){
         printf("\n");
      }
   }
   free(array);
}

/*
 * del_tree(tree)
 * deletes the tree by breadth
 * param: tree to delete
 * post: tree will lose all data and mem location
 * error: cannot create memory for array
 */
void del_tree(struct bin_tree* tree){
   struct avl_link ** array;
   int arr_size = 0, i = 0;
   assert(tree);
   array = malloc(sizeof(struct avl_link*) * (tree->size << 1));
   assert (array);
   array[arr_size ++] = tree->head;
   while(i < arr_size){
      if(array[i]){
         array[arr_size ++] = array[i]->left;
	 array[arr_size ++] = array[i]->right;
      }
      free(array[i]);
   }
   free(array);
   tree->size = 0;
   tree->head = NULL;
}

void _setHeight(struct avl_link* node){
   if(node->left == NULL && node->right == NULL){
      node->height = 0;
   }else if(node->right && node->left){
      node->height = node->right->height > node->left->height ? 
	 node->right->height + 1
	 : node->left->height + 1;
   }else if(node->left){
      node->height = node->left->height + 1;
   }else{
      node->height = node->right->height + 1;
   }
}
struct avl_link * _balance(struct avl_link * node){
  if(node->left){
     _setHeight(node->left);
  }
  if(node->right){
     _setHeight(node->right);
  }

  if(node->left->height - node->right->height > 1){
     if(node->left){
        if(node->left->left && node->left->right && node->left)
     }
  }
}
