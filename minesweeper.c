//p kuti
//created file 30 june 2025

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <termios.h>
#include <time.h>

//TODO
/* implement termios
 * implement the terminal clear screen character '\e[1;1H\e[2J'
 * make a start menu with a start and exit "button" (i want to do this after i implement termios so i can have a cursor go between the options, like the start menu in dwarf fortress)
 * make a method for a game over & one for winning? probably do this once i can actually get the game to work lol (as in after termios is implemented :/)
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

void setFlag(int x, int y, Cell** board) {
	if(!board[y][x].mined) {
		board[y][x].flagged = true;
	}
}

void removeFlag(int x, int y, Cell** board) {
	board[y][x].flagged = false;
}

//to be used by the mineCell method for clearing any cells that have a value of 0
void clearEmptyCells(int x, int y, Cell** board, int size) {
	board[y][x].mined = true;
	if(board[y][x].value > 0) return;
	else {
		for(int i = x - 1; i <= x + 1; i++) {
			for(int j = y - 1; j <= y + 1; j++) {
				if((i == x && j == y) || x == 0 || y == 0 || x == size - 1 || y == size - 1) {
					continue;
				}
				else {
					if(!board[j][i].mined) {
						clearEmptyCells(i, j, board, size);
					}
				}
				
			}
		}
	}
}

void mineCell(int x, int y, Cell** board, int size) {
	if(board[y][x].isMine) {
		//TODO end game method goes here
	}
	clearEmptyCells(x, y, board, size);
}

//0 >= difficultyFactor >= 99
void generateMines(Cell** board, int size, int difficultyFactor) {
	srand(time(NULL));
	
	for(int i = 0; i < size; i++) {
		for(int j = 0; j < size; j++) {
			if(rand() % 100 < difficultyFactor) {
				board[i][j].isMine = true;
			}
		}
	}
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
		free(board[i]);
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

void printMinesweeper() { //art from patorjk.com's text to ascii art generator
	printf(" __   __  ___   __    _  _______  _______  _     _  _______  _______  _______  _______  ______   \n");
	printf("|  |_|  ||   | |  |  | ||       ||       || | _ | ||       ||       ||       ||       ||    _ |  \n");
	printf("|       ||   | |   |_| ||    ___||  _____|| || || ||    ___||    ___||    _  ||    ___||   | ||  \n");
	printf("|       ||   | |       ||   |___ | |_____ |       ||   |___ |   |___ |   |_| ||   |___ |   |_||_ \n");
	printf("|       ||   | |  _    ||    ___||_____  ||       ||    ___||    ___||    ___||    ___||    __  |\n");
	printf("| ||_|| ||   | | | |   ||   |___  _____| ||   _   ||   |___ |   |___ |   |    |   |___ |   |  | |\n");
	printf("|_|   |_||___| |_|  |__||_______||_______||__| |__||_______||_______||___|    |_______||___|  |_|\n");
}

void start() {
	printf("\n");
	printMinesweeper();
	printf("\n\n");
	
	//do some stuff here with like a switch statement or something in conjunction with taking user input with termios idk
	
	printf(">Start<");
}


int main (int argc, char** argv) {
	
	//start();
	
	int boardSize = 20;
	Cell** board = initBoard(boardSize);
	generateMines(board, boardSize, 12);
	
	/*setMine(5, 5, board);
	setMine(6, 5, board);
	setMine(7, 4, board);
	
	setMine(0, 5, board);
	setMine(19, 7, board);
	setMine(5, 0, board);
	setMine(7, 19, board);
	setMine(0, 0, board);
	setMine(0, 19, board);
	setMine(19, 0, board); 
	setMine(19, 19, board);*/
	
	
	
	/*setMine(5, 5, board);
	setMine(6, 5, board);
	setMine(7, 5, board);
	setMine(8, 5, board);
	setMine(9, 5, board);
	setMine(10, 5, board);
	setMine(11, 5, board);
	
	setMine(11, 6, board);
	setMine(11, 7, board);
	setMine(11, 8, board);
	setMine(11, 9, board);
	setMine(11, 10, board);
	setMine(11, 11, board);
	
	setMine(10, 11, board);
	//setMine(9, 11, board);
	//setMine(8, 11, board);
	//setMine(7, 11, board);
	setMine(6, 11, board);
	setMine(5, 11, board);
	
	setMine(5, 10, board);
	setMine(5, 9, board);
	setMine(5, 8, board);
	setMine(5, 7, board);
	setMine(5, 6, board);*/
	
	
	
	
	
	//setMine(0, 5, board);
	
	//TODO do the edge cases for the corners as well
	
	calculateCellMineValue(board, boardSize);
	
	//mineCell(8, 8, board, boardSize);
	
	printBoard(board, boardSize);
	freeBoard(board, boardSize);
	
	
	return EXIT_SUCCESS;
}