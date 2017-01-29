#include <stdio.h>
#include <stdlib.h>

FILE *input_file;

// Function to check if a given choice of a value conflicts with what's already on the board
int check_conflict(int value, int cell, int* board) {
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
	int x2 = x / 3;
	int y2 = y / 3;
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

// printing board function
void print_board(int* board) {
	int i, j;
	for(i = 0; i < 9; i++) {
		for(j = 0; j < 9; j++) {
			printf("%d", board[j + 9*i]);
		}
		printf("\n");
	}
	printf("\n");
}

// perform dfs
int dfs(int i, int val, int* board) {
	if (i == 81) {
		return 1; // we reached the last cell
	} else {
		int j;
		if (!board[i] && !check_conflict(val, i, board)) {
			// check that current cell isn't empty and we canput 
			// val in it. If not...
			return 0;
		} else {
			for (j = 1; j < 10; j++) {
				if (dfs(i++, j, board)) {
					if (!board[i]) {
						board[i] = val;
					}
					return 1;
				} else {
					return 0;
				}
			}
		}
	}
	return 0;
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
	
	print_board(board);

	// perform dfs
	dfs(0,1,board);
	print_board(board);
	//printf("%d\n", check_conflict(3,78, board));
	//printf("%d\n", check_conflict(7,78, board));	
	void free(void *board);
	return 0;

}
