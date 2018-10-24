# DataStructures
Synopsis:
Practicing basic data structures using ANSI C implementations.
Currently hosting an AVL BST structure

Code Example:
just include an unlinked version of the compiled avl_tree.c file.
You can feel free to add to this code but all the private functionality is not necessary for use.
(Private functionality has a function with a _ leading character)

The binary tree header file represents the macros and dynamic interface you must adhere to 
your own project.

#include binary_tree.h
#undef TYPE
#define TYPE myStruct

#undef LT
#define LT(A, B) (A < B) /* Or something that returns 1 for Less than */
                         /* and 0 for otherwise */

#undef EQ
#define EQ(A, B) (A == B) /* Or something that returns 1 for Equivalence and 0 for otherwise */
int main(){
   struct bin_tree a;
   struct myStruct b;
   init_tree(&a);
   add_tree(&a, b); /* Copied by Value */
   print_tree(&a); /* avl_tree.c may need to be edited for it's print functionality as commented */
   del_tree(&a);
   return 0;
}

Motivation:
This is mainly in efforts to show my skills in data structures.

Installation:
Currently all the source files are in the repository. No additional installation is required!
Just download the source files into your build. These do not use platform specific libraries!

Tests:
The last two functions adequately test that the structure is still sound.
IS_AVL will return 1 if the tree is still balanced
IS_BIN_TREE will return 1 if the tree is still sorted

License:
I believe these functions are really too simple to license. Copy at your own risk but I can not be
held liable for destruction of other property.
