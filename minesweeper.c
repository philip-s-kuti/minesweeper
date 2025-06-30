//p kuti
//created file 30 june 2025

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//TODO
/* the whole calculateCellMineValue
 * implement termios
 * implement the terminal clear screen character '\e[1;1H\e[2J'
*/

typedef struct Cell Cell;
struct Cell {
	bool isMine; //whether the cell contains a mine or not
	int value; //how many mines are around the cell
};

void initCell (Cell* c, bool isMine) {
	c->isMine = isMine;
	c->value = 0;
}

//TODO
void calculateCellMineValue(Cell* c) {
	//TODO look at the 8 cells around every mine cell
	//and increment them all by 1
	//make sure to check for edge cases. literally in this case (only have to increment 5 cells when a mine is against the side of the board)
}

Cell** initBoard(int boardSize) { //since the board will always be square, we just take one value and square it for the dimensions of the board
	
	//malloc the board
	Cell** c = malloc(sizeof(Cell) * boardSize);
	for(int i = 0; i < boardSize; i++) {
		c[i] = malloc(sizeof(Cell) * boardSize);
	}
	
	//set the initial values
	for(int i = 0; i < boardSize; i++) {
		for(int j = 0; j < boardSize; j++) {
			c[i][j].value = 0;
			c[i][j].isMine = false;
		}
	}
	return c;
}


void printBoard(Cell** board, int size) {
	
	for(int i = 0; i < size; i++) {
		for(int j = 0; j < size; j++) {
				
			if(board[i][j].isMine) {
				printf("O");
			}
			else {
				if(board[i][j].value > 0) {
					printf("%d", board[i][j].value);
				}
				else {
					printf(".");
				}
			}
			printf(" "); //for spacing
		}
		printf("\n");
	}
	
}


int main (int argc, char** argv) {
	
	int boardSize = 20;
	Cell** board = initBoard(boardSize);
	printBoard(board, boardSize);
	
	
	
	return EXIT_SUCCESS;
}