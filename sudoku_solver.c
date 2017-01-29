#include <stdio.h>
#include <stdlib.h>

FILE *input_file;

// Function to check if a given choice of a value conflicts with what's already on the board
int checkConflict(const int value, const int cell, const int* board) {
	int x = cell % 9; // column
	int y = cell / 9; // row
	int i, j;
	int result = 1;

	// check row conflicts
	for (i = 0; i < 9; i++) {
		if (board[cell-x+i] == value) {
			result = 0;
		}
	}

	// check column conflicts
	for (i = 0; i < 9; i++) {
		if (board[x + 9*i] == value) {
			result = 0;
		}
	}

	// check small squares
	// work out which small square we're in
	int x2 = (x / 3) * 3;
	int y2 = (y / 3) * 3;
	// iterate over the cells in that square
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			if (board[x2 + i + (y2 + j) * 9] == value) {
				result = 0;
			}
		}
	}
	return result;
}

// DFS
int dfs(int* board) {

}

int main(int argc, char *argv[]) {
    input_file = fopen(argv[1], "r");
    
    // check that we were given a file
    if (input_file == NULL) {
	 printf("invalid file\n");
	 return 1;
    }  
    
    int i = 0;
    int j;
    char buff[256];

    // read file and record what's on the board
    int *board = (int*) malloc(sizeof(int) * 81);
      
    while(fgets(buff, sizeof(buff), input_file) && i < 9) {
    	 for (j = 0; j < 9; j++) {
		int x = buff[j] - '0';
		if (0 <= x && x < 10) {
			board[j + 9*i] = x;
		} else {
			board[j + 9*i] = 0;
		}
	 }
	 i++;
    }
    
    // print the original board
    printf("The original board is:\n");
    for(i = 0; i < 9; i++) {
	for(j = 0; j < 9; j++) {
		printf("%d", board[j + 9*i]);
	}
	printf("\n");
    }

    printf("\nThe solution is:\n");
    // perform dfs
    printf("%d\n", checkConflict(3,2, board));
    printf("%d\n", checkConflict(4,2, board));    
    void free(void *board);
    return 0;

}
