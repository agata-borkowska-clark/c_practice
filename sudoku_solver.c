#include <stdio.h>
#include <stdlib.h>


// Proposed representation of a board: each tile is a 4-tuple (digit, row, column, 
// square), recorded in an array
FILE *input_file;



int main(int argc, char *argv[]) {
  int error = 0;
  while (error == 0) {
    int *board = (int *) malloc(sizeof(int) * 81);
    // record input
    char buff[255];
    input_file = fopen(argv[0], "r");
    if (input_file == NULL) {
	  printf("invalid file");
	  error = 1;
    }  
  
    fscanf(input_file, "%s", buff);
    printf("1. - %s\n", buff);

    // perform dfs
    break;
  }
  return error;

}
