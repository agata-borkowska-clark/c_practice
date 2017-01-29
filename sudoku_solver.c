#include <stdio.h>
#include <stdlib.h>

FILE *input_file;
// enumerate return codes
typedef enum {
	SUCCESS=1, 
	CONFLICT_IN_ROW, 
	CONFLICT_IN_COLUMN, 
	CONFLICT_IN_SUB_SQUARE
} Check_Status;

// Function to check if a given choice of a value conflicts with what's already on the board
Check_Status check_conflict(int cell, int value, int* board) {
	int x = cell % 9; // column
	int y = cell / 9; // row
	Check_Status result = SUCCESS;

	// check row conflicts
	int i, j;
	for (i = 0; i < 9; i++) {
		if (board[cell-x+i] == value && cell - x + i != cell) {
			result = CONFLICT_IN_ROW;
			break;
		}
	}

	// check column conflicts
	for (i = 0; i < 9; i++) {
		if (board[x + 9*i] == value && x + 9 * i != cell) {
			result = CONFLICT_IN_COLUMN;
			break;
		}
	}

	// Check small squares:
	// Work out which small square we're in.
	int x2 = (x / 3) * 3;
	int y2 = (y / 3) * 3;
	// Iterate over the cells in that square.
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			if (board[x2 + i + (y2 + j) * 9] == value 
					&& x2 + i + (y2+j) * 9 != cell) {
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
		printf("\n"); // Print new line at the end of the row.
	}
	printf("\n"); // Print a space to separate it from further output.
}

// perform dfs
Check_Status dfs(int cell, int* board) {
	if (cell == 81) {
		return SUCCESS; // We reached the last cell, succscience.
	} else if (board[cell]) {
		Check_Status result = check_conflict(cell, board[cell], board);
		if (result == SUCCESS) {
			return dfs(cell + 1, board); // This cell is filled from the 
			// start, so we just need to pass on the result of its children
		} else {
			return result;
		}
	} else {
		Check_Status result;
		for (int j = 1; j < 10; j++){
			// This is an empty cell, so we check each of 1-9.
			result = check_conflict(cell, j, board); 
			if (result == SUCCESS) {
				// We can put j in this cell, so we do it
				// *temporarily* and check if children still
				// can be filled.
				board[cell] = j;
				Check_Status child = dfs(cell + 1, board);
				if (child == SUCCESS) {
					return SUCCESS; // j gives a feasible
					// solution to the whole board
				} else {
					board[cell] = 0; // Erase the value we 
					// have tried to put in there.
					result = child;
				}
			}
		}
		return result;
	}	
}

int main(int argc, char *argv[]) {
	input_file = fopen(argv[1], "r");
	
	// Check that we were given a file.
	if (input_file == NULL) {
		printf("invalid file\n");
		return 1;
	}  
	
	// Read file and record what's on the board.
	int *board = (int*) malloc(sizeof(int) * 81);
	  
	char buff[128]; // We probably don't need that many characters, but...
	int i = 0;
	while(fgets(buff, sizeof(buff), input_file) && i < 9) {
		for (int j = 0; j < 9; j++) {
			// We convert char to int by taking the char's code and
			// subtracting the code of '0' from it.
			int x = buff[j] - '0';
			if (0 <= x && x < 10) {
				board[j + 9*i] = x;
			} else {
				// If the character isn't a digit, the input
				// is very wrong.
				printf("This is not a board!\n");
				return 1;
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
	void free(void *board);
	return 0;

}
