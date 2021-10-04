#include <iostream>

struct coord {
	int row;
	int col;
	int value = 0;
	coord() {
		row = 0;
		col = 0;
	}
	coord(int row, int col) {
		this->row = row;
		this->col = col;
	}
};


/*****
* Globals
*****/
// integer board for easy editing
int numBoard[9][9] = {
	{1, 7, 4, 9, 6, 3, 8, 5, 2}, 
	{2, 8, 5, 1, 7, 4, 9, 6, 3}, 
	{3, 9, 6, 2, 8, 5, 1, 7, 4}, 
	{4, 1, 7, 3, 9, 6, 2, 8, 5}, 
	{5, 2, 8, 4, 1, 7, 3, 9, 6}, 
	{6, 3, 9, 5, 2, 8, 4, 1, 7}, 
	{7, 4, 1, 6, 3, 9, 5, 2, 8}, 
	{8, 5, 2, 7, 4, 1, 6, 3, 9}, 
	{9, 6, 3, 8, 5, 2, 7, 4, 1} 
};

// coord struct board for easy access
coord board[9][9];


/*****
* Function Prototypes
*****/
void printBoard();
bool checkRow(int n, coord cord);
bool checkCol(int n, coord c);
bool checkSquare(int n, coord c);
bool checkSpace(int n, coord c);
bool checkSolution();
int findClosest3(int n);


/*****
* Functions
*****/
int main()
{
	// fill board array
	for (int r = 0; r < 9; r++) {
		for (int c = 0; c < 9; c++) {
			board[r][c].col = c;
			board[r][c].row = r;
			board[r][c].value = numBoard[r][c];
		}
	}

	printBoard();

	if (checkSolution())
		std::cout << "You did it!\n";
	else
		std::cout << "Keep trying\n";
}

void printBoard() {
	for (int r = 0; r < 9; r++) {
		for (int c = 0; c < 9; c++)
			std::cout << board[r][c].value << " ";
		std::cout << std::endl;
	}
}

bool checkRow(int n, coord cord) {
	// return true if number is available in row
	for (int col = 0; col < 9; col++) {
		if (board[cord.row][col].value == n && col != cord.col) { // same row, different columns
			std::cout << "Failed row check\n"; // for testing
			return false;
		}
	}
	return true;
}

bool checkCol(int n, coord cord) {
	// return true if number is available in column
	for (int row = 0; row < 9; row++) {
		if (board[row][cord.col].value == n && row != cord.row) { // same column, different rows
			std::cout << "Failed col check\n"; // for testing
			return false;
		}
	}
	return true;
}

bool checkSquare(int n, coord cord) {
	// return true if number is available in 3 by 3 square

	int c = findClosest3(cord.col); // top left 
	int r = findClosest3(cord.row); // corner of box

	for (int row = r; row < r + 3; row++) {
		for (int col = c; col < c + 3; col++) {
			if (board[row][col].value == n && row != cord.row && col != cord.col) { // confined to 3 by 3 area starting in top left corner
				std::cout << "Failed square check\n"; // for testing
				return false;
			}
		}
	}
	return true;
}

bool checkSpace(int n, coord cord) {
	// return true if number is available in space
	return checkCol(n, cord) && checkRow(n, cord) && checkSquare(n, cord);
}

bool checkSolution() {
	// check if puzzle has been completed
	for (int r = 0; r < 9; r++) {
		for (int c = 0; c < 9; c++) {
			if (!checkSpace(board[r][c].value, board[r][c])) {
				std::cout << r << c << std::endl; // testing
				return false;
			}
		}
	}
	return true;
}

int findClosest3(int n) {
	// find the closest multiple of 3 less than n
	for (int i = n; i >= 0; i--) {
		if (i % 3 == 0) return i;
	}
	return 0;
}