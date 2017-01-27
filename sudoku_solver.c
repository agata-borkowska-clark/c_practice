#include <stdio.h>
#include <stdlib.h>

FILE *input_file;
//int *board[81];

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
    int *board = (int*) malloc(sizeof(int) * 81);
    //  
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
    
    for(i = 0; i < 9; i++) {
	for(j = 0; j < 9; j++) {
		printf("%d", board[j + 9*i]);
	}
	printf("\n");
    }
    // perform dfs
    
    void free(void *board);
    return 0;

}
