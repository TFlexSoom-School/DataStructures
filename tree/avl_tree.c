/*
 * Tristan Hilbert
 * 6/10/18
 * AVL Binary Tree implementation
 *
 */

/* For type information and bin tree interface */
#include "binary_tree.h"

/* For Print Function. Uses Print f assuming stdout stream */
#include <stdio.h>

/* For use of NULL */
#include <stdlib.h>

/* For use of assert function */
#include <assert.h>

/* Struct Definitions */
struct avl_link {
   TYPE data;
   int height;
   struct avl_link* left;
   struct avl_link* right;
};


/* Struct Definitions END */

/******************************************/

/* Function Prototypes */

void _setHeight(struct avl_link*);
int _compareHeight(struct avl_link*, struct avl_link*);
struct avl_link * _balance(struct avl_link *);
struct avl_link * _rotateLeft(struct avl_link*);
struct avl_link * _rotateRight(struct avl_link*);

/* End Function Prototypes */

/* Function Definitions * ******************************/

/* Initialize Tree with default values
 * Fails assertion check if pointer is not NULL */
void init_tree(struct bin_tree* tree) {
   assert(tree);
   tree->head = NULL;
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
void add_tree(struct bin_tree* tree, TYPE e) {
   assert(tree);
   tree->head = _add_node_r(tree->head, e);
   tree->size++;

}

/* Recursive call to the above function */
struct avl_link * _add_node_r(struct avl_link* node, TYPE e) {
   if (node) {
      if (LT(e, node->data)) {
	 node->left = _add_node_r(node->left, e);
      }else{
	 node->right = _add_node_r(node->right, e);
      }
      return _balance(node);
   }
   else {
      node = malloc(sizeof(struct avl_link));
      assert(node);
      node->data = e;
      node->height = 0;
      node->left = 0;
      node->right = 0;
      return node;
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
void remove_tree(struct bin_tree* tree, TYPE e) {
   assert(tree);
   tree->head = remove_tree_r(tree->head, e);
   tree->size--;
}

/* Recursive call to funtion above */
struct avl_link * remove_tree_r(struct avl_link* node, TYPE e) {
   if (node) {
      if (EQ(node->data, e)) {
	 return _new_data_remove(node);
      }
      else if (LT(e, node->data)) {
	 remove_tree_r(node->left, e);
      }
      else {
	 remove_tree_r(node->right, e);
      }
      return _balance(node);
   }
   return node;
}

/* Assigns the right most data to the node or removes the node entirely */
struct avl_link*  _new_data_remove(struct avl_link* node) {
   struct avl_link * it;
   TYPE temp;
   if (node->right) {

      it = node->right;
      if (it->left == NULL) {
	 temp = it->data;
	 free(node->right);
	 node->right = NULL;
	 node->data = temp;
	 return node;
      }

      while (it->left->left) {
	 it = it->left;
      }
      temp = it->left->data;
      free(it->left);
      it->left = NULL;
      node->data = temp;
      return node;

   }
   else {
      it = node->left;
      free(node);
      return it;
   }
}

/* Returns minimum most value of the tree */
TYPE get_min(struct bin_tree* tree) {
   struct avl_link * it;
   assert(tree);
   it = tree->head;
   while (it->left) {
      it = it->left;
   }
   return it->data;
}

/* Returns the maximum most value of the tree */
TYPE get_max(struct bin_tree* tree) {
   struct avl_link * it;
   assert(tree);
   it = tree->head;
   while (it->right) {
      it = it->right;
   }
   return it->data;
}

/* Prints Breadth of Tree */
void _format_spaces(int);
void print_tree(struct bin_tree* tree) {
   struct avl_link ** array;
   int arr_size = 0, i = 0, j = 0;
   assert(tree);
   
   if(tree->head){
      array = malloc(sizeof(struct avl_link*) * (4 << tree->head->height));
      assert(array);
   }else{
      return; /* No tree to print */
   }
   
   for (i = 0; i < tree->size * 2; i++) {
      array[i] = 0;
   }
   
   i = 0;
   array[arr_size++] = tree->head;
   while (i < arr_size) {
      if (array[i]) {
	 printf("| %d |", array[i]->data); /* Should be %d %g not %d %d */
	 array[arr_size++] = array[i]->left;
	 array[arr_size++] = array[i]->right;
      }else{
         printf("|NULL|");
      }

      j = i + 2;
      if (((((j << 1) - 1)^j) + 1)== j){ /* Is i a power of 2 */
	 printf("\n");
      }
      i++;
   }
   printf("\n");
   free(array);
}

/*
 * del_tree(tree)
 * deletes the tree by breadth
 * param: tree to delete
 * post: tree will lose all data and mem location
 * error: cannot create memory for array
 */
void del_tree(struct bin_tree* tree) {
   struct avl_link ** array;
   int arr_size = 0, i = 0;
   assert(tree);
   if(tree->head){
      array = malloc(sizeof(struct avl_link*) * (tree->size));
      assert(array);
      array[arr_size++] = tree->head;
      while (i < arr_size) {
	 if (array[i]) {
	    if(array[i]->left)
	       array[arr_size++] = array[i]->left;
	    if(array[i]->right)
	       array[arr_size++] = array[i]->right;
	    free(array[i]);
	 }
	 i++;
      }
      free(array);
   }
   tree->size = 0;
   tree->head = NULL;
}

/* Sets height of the current node based off of its children */
void _setHeight(struct avl_link* node) {
   if (node->left == NULL && node->right == NULL) {
      node->height = 0;
   }
   else if (node->right && node->left) {
      node->height = node->right->height > node->left->height ?
	 node->right->height + 1
	 : node->left->height + 1;
   }
   else if (node->left) {
      node->height = node->left->height + 1;
   }
   else {
      node->height = node->right->height + 1;
   }
}

/* Balances the tree around the given node.
 * Assumes that both left and right nodes have children
 *    with correct heights 
 */
struct avl_link * _balance(struct avl_link * node) {
   if (node->left) {
      _setHeight(node->left);
   }
   if (node->right) {
      _setHeight(node->right);
   }

   if (_compareHeight(node->left, node->right) >= 2) {
      if (node->left) {
	 if (_compareHeight(node->left->left, node->left->right) <= -1) {
	    node->left = _rotateLeft(node->left);
	 }
	 return _rotateRight(node);
      }
   }
   else if (_compareHeight(node->left, node->right) <= -2) {
      if (node->right) {
	 if (_compareHeight(node->right->left, node->right->right) >= 1) {
	    node->left = _rotateRight(node->right);
	 }
	 return _rotateLeft(node);
      }

   }
   return node;
}

/* Compares the heights of the two nodes
 *    Pos return means a is heavier
 *    Neg return means b is heavier
 *    |2| =< height means rotation
 */
int _compareHeight(struct avl_link* a, struct avl_link* b) {
   if (a && b) {
      return a->height - b->height;
   }
   else if (a) {
      return a->height + 1;
   }
   else if (b) {
      return (0 - b->height - 1);
   }
   else {
      return 0;
   }
}


/*
 * rotate Functions:
 * pre conditions -> Side is right or left heavy so
 *    node and node->left or node->right is defined not NULL
 *
 */

struct avl_link * _rotateLeft(struct avl_link* node) {
   struct avl_link * temp;
   temp = node->right;
   node->right = temp->left;
   temp->left = node;
   _setHeight(node);
   _setHeight(temp);
   return temp;
}

struct avl_link * _rotateRight(struct avl_link* node) {
   struct avl_link * temp;
   temp = node->left;
   node->left = temp->right;
   temp->right = node;
   _setHeight(node);
   _setHeight(temp);
   return temp;
}

int _r_is_avl(struct avl_link*);
int IS_AVL(struct bin_tree* tree){
   assert(tree);
   return _r_is_avl(tree->head);
}

int _r_is_avl(struct avl_link* node){
   int l, r;
   /* Recursive Calls */
   if(node){
      l = _r_is_avl(node->left);
      r = _r_is_avl(node->right);
      if(l & r != 1){
	 return 0;
      }
      if(node->left)
	 _setHeight(node->left);
      if(node->right)
	 _setHeight(node->right);
      l = _compareHeight(node->left, node->right);
      if(l >= 2 || l <= -2){
	 return 0;
      }
   }
   return 1;
}

int IS_BIN_TREE(struct bin_tree* tree){
   struct avl_link ** array;
   struct bin_tree temp;
   int arr_size = 0, i = 0;
   assert(tree);
   if(tree->head){
      array = malloc(sizeof(struct avl_link*) * (tree->size));
      assert(array);
      array[arr_size++] = tree->head;
      while (i < arr_size) {
	 if (array[i]) {
	    if(array[i]->left){
	       temp.head = array[i]->left;
	       if(!LT(get_max(&temp), array[i]->data)){
		  free(array);
		  return 0;
	       }else{
		  array[arr_size++] = array[i]->left;
	       }
	    }if(array[i]->right){
	       temp.head = array[i]->right;
	       if(!LT(array[i]->data, get_min(&temp))){
		  free(array);
		  return 0;
	       }else{
		  array[arr_size++] = array[i]->right;
	       }
	    }
	    i++;
	 }
	 free(array);
	 return 1;
      }
      return 0;
   }
}

/* End Function Definitions * ******************************/
