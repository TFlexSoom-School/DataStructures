/*
 * Tristan Hilbert
 * 6/10/2018
 * Main Function Testing
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include "tree/binary_tree.h"

int main(int argc, char * argv[]) {
   FILE * text_input;
   int i, j;
   struct bin_tree a;

   if (!argv[1]) {
      printf("Needed Arguments:\n\tText File \".txt\"\n");
      return 1;
   }
   else {

      init_tree(&a);
      text_input = fopen(argv[1], "r");
      while ((fscanf(text_input, "%i", &i)) != EOF) {
	      add_tree(&a, i);
      }
      printf("\n\n");
      fclose(text_input);
      print_tree(&a);
      printf("\n");
      remove_tree(&a, i);
      printf("It is an AVL_TREE if the following %d is 1\n", IS_AVL(&a));
      printf("but it is a BIN_TREE if the following %d is a 1\n", IS_BIN_TREE(&a));
      add_tree(&a, 25);
      print_tree(&a);
      i = b_tree_contains(&a, 25);
      printf("Tree can find containing element if %d is 1\n", i);
      remove_tree(&a, 25);
      i = b_tree_contains(&a, 25);
      printf("Unless included in the text file 25 is said not to be in the tree if %d is 0\n", i);
      del_tree(&a);
   }
   return 0;
}
