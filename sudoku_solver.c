#include <stdio.h>
#include <stdlib.h>


// Proposed representation of a board: each tile is a 4-tuple (digit, row, column, 
// square), recorded in an array
FILE *input_file;



int main(int argc, char *argv[]) {
  
  int *board = (int *) malloc(sizeof(int) * 81);
  // record input
  char buff[255];
  input_file = fopen(argv[0], "r");
  fscanf(input_file, "%s", buff);
  printf(input_file,"1. - %s\n", buff);

  // perform dfs
    

}
