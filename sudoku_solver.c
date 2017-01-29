#include <stdio.h>
#include <stdlib.h>

FILE *input_file;
typedef enum {SUCCESS, CONFLICT_IN_ROW, CONFLICT_IN_COLUMN, CONFLICT_IN_SUB_SQUARE} Check_Status;

// Function to check if a given choice of a value conflicts with what's already on the board
Check_Status check_conflict(int cell, int value, int* board) {
	int x = cell % 9; // column
	int y = cell / 9; // row
	int i, j;
	Check_Status result = SUCCESS;

	// check row conflicts
	for (i = 0; i < 9; i++) {
		if (board[cell-x+i] == value) {
			result = CONFLICT_IN_ROW;
			break;
		}
	}

	// check column conflicts
	for (i = 0; i < 9; i++) {
		if (board[x + 9*i] == value) {
			result = CONFLICT_IN_COLUMN;
			break;
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
				result = CONFLICT_IN_SUB_SQUARE;
				break;
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
Check_Status dfs(int cell, int* board) {
	if (cell == 81) {
		return SUCCESS; // we reached the last cell
	} else if (board[cell]) {
		return dfs(cell + 1, board);
	} else {
		Check_Status result;
		for (int j = 1; j < 10; j++){
			result = check_conflict(cell, j, board); 
			if (result == SUCCESS) {
				// check that current cell isn't empty and we can put 
				// j in it. If so,
				board[cell] = j;
				Check_Status child = dfs(cell + 1, board);
				if (child == SUCCESS) {
					return SUCCESS;
				} else {
					board[cell] = 0;
					result = child;
				}
			}
		}
		return result;
	}	
}

int main(int argc, char *argv[]) {
	input_file = fopen(argv[1], "r");
	
	// check that we were given a file
	if (input_file == NULL) {
		printf("invalid file\n");
		return 1;
	}  
	
	// read file and record what's on the board
	int *board = (int*) malloc(sizeof(int) * 81);
	  
	char buff[256];
	int i = 0;
	while(fgets(buff, sizeof(buff), input_file) && i < 9) {
		for (int j = 0; j < 9; j++) {
			int x = buff[j] - '0';
			if (0 <= x && x < 10) {
				board[j + 9*i] = x;
			} else {
				board[j + 9*i] = 0;
			}
	 	}
		i++;
	}
	
	printf("This is the original board:\n");
	print_board(board);

	// perform dfs
	
	if(dfs(0, board) == SUCCESS) {
		printf("This is the solution:\n");
		print_board(board);
	} else {
		printf("The board is incorrect\n");
	}
	//printf("%d\n", check_conflict(3,78, board));
	//printf("%d\n", check_conflict(7,78, board));	
	void free(void *board);
	return 0;

}
