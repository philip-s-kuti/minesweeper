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

//only need to call this once at the beginning of the program
//should probably make this more dry but whatever. maybe later
//looks at every cell around a mine and increments their values by one
//i could check to see if a cell has a mine in it and skip the increment, but i really dont care enough for that
//the mine cell's value isnt ever used anyways so it's fine
void calculateCellMineValue(Cell** board, int size) {
	
	for(int i = 0; i < size; i++) {
		for(int j = 0; j < size; j++) {
			if(board[i][j].isMine) {
				if(i == 0) { //check if the mine is on the row
					
					if(j == 0) { //if the mine is in the top left corner
						for(int k = 0; k < 2; k++) {
							for(int p = 0; p < 2; p++) {
								board[i + (k)][j + (p)].value++;
							}
						}
					}
					
					else if(j == size - 1) { //if the mine is in the top right corner
						for(int k = 0; k < 2; k++) {
							for(int p = 0; p < 2; p++) {
								board[i + (k)][j + (p - 1)].value++;
							}
						}
					}
					
					else {
						for(int k = 0; k < 2; k++) {
							for(int p = 0; p < 3; p++) {
								board[i + (k)][j + (p - 1)].value++;
							}
						}
					}
				}
				
				else if(i == size - 1) { //check if the mine is on the last row
					
					if(j == 0) { //if the mine is in the bottom left corner
						for(int k = 0; k < 2; k++) {
							for(int p = 0; p < 2; p++) {
								board[i + (k - 1)][j + (p)].value++;
							}
						}
					}
					
					else if(j == size - 1) { //if the mine is in the bottom right corner
						for(int k = 0; k < 2; k++) {
							for(int p = 0; p < 2; p++) {
								board[i + (k - 1)][j + (p - 1)].value++;
							}
						}
					}
					else {
						for(int k = 0; k < 2; k++) {
							for(int p = 0; p < 3; p++) {
								board[i + (k - 1)][j + (p - 1)].value++;
							}
						}
					}
				}
				
				else if(j == 0) { //check if the mine is on the first column
					
					for(int k = 0; k < 3; k++) {
						for(int p = 0; p < 2; p++) {
							board[i + (k - 1)][j + (p)].value++;
						}
					}
					
				}
				
				else if(j == size - 1) { //check if the mine is on the last column
					
					for(int k = 0; k < 3; k++) {
						for(int p = 0; p < 2; p++) {
							board[i + (k - 1)][j + (p - 1)].value++;
						}
					}
					
				}
				
				else { //otherwise the mine is somewhere in the middle of the board
					for(int k = 0; k < 3; k++) {
						for(int p = 0; p < 3; p++) {
							board[i + (k - 1)][j + (p - 1)].value++;
						}
					}
				}
			}
		}
	}		
}

//set a mine on the board using an x y coordinate
//REMEMBER that the board coordinates start at 0, so 5, 5 would actually be "6, 6" in a coordinate system starting at 1's. just keep that in mind
void setMine(int x, int y, Cell** board) {
	board[y][x].isMine = true;
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

void printMinesweeper() {
	printf(" __   __  ___   __    _  _______  _______  _     _  _______  _______  _______  _______  ______   \n");
	printf("|  |_|  ||   | |  |  | ||       ||       || | _ | ||       ||       ||       ||       ||    _ |  \n");
	printf("|       ||   | |   |_| ||    ___||  _____|| || || ||    ___||    ___||    _  ||    ___||   | ||  \n");
	printf("|       ||   | |       ||   |___ | |_____ |       ||   |___ |   |___ |   |_| ||   |___ |   |_||_ \n");
	printf("|       ||   | |  _    ||    ___||_____  ||       ||    ___||    ___||    ___||    ___||    __  |\n");
	printf("| ||_|| ||   | | | |   ||   |___  _____| ||   _   ||   |___ |   |___ |   |    |   |___ |   |  | |\n");
	printf("|_|   |_||___| |_|  |__||_______||_______||__| |__||_______||_______||___|    |_______||___|  |_|\n");
}

void start() {
	printf("\n\n");
	printMinesweeper();
	printf("\n\n");
}


int main (int argc, char** argv) {
	
	start();
	
	int boardSize = 20;
	Cell** board = initBoard(boardSize);
	
	setMine(5, 5, board);
	setMine(6, 5, board);
	setMine(7, 4, board);
	
	setMine(0, 5, board);
	setMine(19, 7, board);
	setMine(5, 0, board);
	setMine(7, 19, board);
	setMine(0, 0, board);
	setMine(0, 19, board);
	setMine(19, 0, board); 
	setMine(19, 19, board);
	
	//setMine(0, 5, board);
	
	//TODO do the edge cases for the corners as well
	
	calculateCellMineValue(board, boardSize);
	
	printBoard(board, boardSize);
	
	
	
	return EXIT_SUCCESS;
}