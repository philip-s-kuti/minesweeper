//p kuti
//created file 30 june 2025

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <termios.h>

//TODO
/* implement termios
 * implement the terminal clear screen character '\e[1;1H\e[2J'
 * make a start menu with a start and exit "button" (i want to do this after i implement termios so i can have a cursor go between the options, like the start menu in dwarf fortress)
 * make a method for mining a cell, also make a helper method that will clear all cells that have a value equal to 0
 * make a method for flagging a cell
 * make a method for a game over & one for winning? probably do this once i can actually get the game to work lol (as in after termios :/)
 * also for the game over, i want the mine the user mined to blink in and out to make it very clear where they messed up lol
*/

typedef struct Cell Cell;
struct Cell {
	bool isMine; //whether the cell contains a mine or not
	bool flagged; //whether a flag has been placed on the cell
	bool mined; //whether the user has mined the cell
	int value; //how many mines are around the cell
};

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
			c[i][j].mined = true;
			c[i][j].flagged = false;
		}
	}
	return c;
}

void freeBoard(Cell** board, int size) {
	for(int i = 0; i < size; i++) {
		free(board[i])
	}
	free(board);
}


void printBoard(Cell** board, int size) {
	
	for(int i = 0; i < size; i++) {
		for(int j = 0; j < size; j++) {
			
			if(!board[i][j].mined) {
				printf("■"); //U+25A0
			}
			
			else if(board[i][j].flagged) {
				printf("⚑"); //flag character U+2691
			}
			
			else {
				if(board[i][j].isMine) {
					printf("!");
				}
				else {
					if(board[i][j].value > 0) {
						printf("%d", board[i][j].value);
					}
					else {
						printf("⬞"); //small square U+25AB
					}
				}
			}
			printf(" "); //for spacing, since printing in the terminal makes characters on different lines further apart than when they are in sequence
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
	freeBoard(board, boardSize);
	
	
	return EXIT_SUCCESS;
}