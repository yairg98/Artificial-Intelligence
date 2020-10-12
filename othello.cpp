
#include "othello.h"
#include <iostream>
#include <windows.h>
#include <string>

using namespace std;



// Constructor for 'othello' class
othello::othello(int b[8][8], int t, int m) {
	
	board = b;
	turn = t;
	moves = m;
		
	// Printable representation of blank/black/white spaces
	spaces[0] = "\033[42m\u0020\u0020\u0020\033[31;42m\u2502\033[m";
    spaces[1] = "\033[30;42m\u2590\u2588\u258C\033[31;42m\u2502\033[m";
    spaces[2] = "\033[97;42m\u2590\u2588\u258C\033[31;42m\u2502\033[m";	
	
	// rowDivider is printed between piece-rows to create the board grid
    string horizontal = "\033[31;42m\u2500\033[m";
    string intersection = "\033[31;42m\u253C\033[m";
    string divSpace = horizontal+horizontal+horizontal+intersection;
    for (int i=0; i<9; i++) { rowDivider += divSpace; }
	
	// columnLabels is printed at the top of board
	columnLabels = "\033[42m\u0020\u0020\u0020\033[31;42m\u2502\033[m";
	for (char i='A'; i<='H'; i++) {
		columnLabels += "\033[97;42m\u0020";
		columnLabels += string(1,i); // conversion not necessary
		columnLabels += "\u0020\033[31;42m\u2502\033[m";
	}
	
}


// Print the board
int othello::print(int b[8][8]) {	
	cout << columnLabels << endl;
	cout << rowDivider << endl;
	for (int i=0; i<8; i++) {
		cout << "\033[97;42m " << (i+1) << " \033[31;42m\u2502\033[m";
		for (int j=0; j<8; j++) {
			cout << spaces[b[i][j]];
		}
		cout << endl << rowDivider << endl;
	}
	
	return 1;
}


// Test board data member
void othello::getBoard() {
	for (int i=0; i<8; i++) {
		for (int j=0; j<8; j++) {
			cout << board[i][j] << endl;;
		}
		cout << endl;
	}
	cout << "********" << moves << endl;
}


int main() {
	
	// Test board to print
	int board[8][8] = {
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,1,2,0,0,0},
		{0,0,0,2,1,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0}
	};

	othello game = othello(board, 5, 5);
	
	game.getBoard();
	
	game.print(board);
	
	return 1;
}


