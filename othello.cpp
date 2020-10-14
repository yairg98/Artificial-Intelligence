
#include "othello.h"
#include <iostream>
#include <windows.h>
#include <string>

using namespace std;


othello::othello(int (&b)[8][8], int t) {
	for (int i=0; i<10; i++) {
		board[0][i] = 3;
		board[9][i] = 3;
		board[i][0] = 3;
		board[i][9] = 3;
	}
	for (int i=1; i<9; i++) {
		for (int j=1; j<9; j++) {
			board[i][j] = b[i-1][j-1];
		}
	}
	turn = t;
		
	// Printable representation of blank/black/white spaces
	spaces[0] = "\033[42m\u0020\u0020\u0020\033[31;42m\u2502\033[m";
    spaces[1] = "\033[30;42m\u2590\u2588\u258C\033[31;42m\u2502\033[m";
    spaces[2] = "\033[97;42m\u2590\u2588\u258C\033[31;42m\u2502\033[m";	
	
	// rowDivider is printed between piece-rows to create the board grid
    string divSpace = "\033[31;42m\u2500\u2500\u2500\u253C\033[m";
    for (int i=0; i<9; i++) { rowDivider += divSpace; }
	
	// columnLabels is printed at the top of board
	columnLabels = "\033[42m\u0020\u0020\u0020\033[31;42m\u2502\033[m";
	for (char i='A'; i<='H'; i++) {
		columnLabels += "\033[97;42m\u0020";
		columnLabels += string(1,i); // conversion not necessary
		columnLabels += "\u0020\033[31;42m\u2502\033[m";
	}
	
	// Set initial legal moves
	findMoves();
}


int othello::print() {

	string num;
	cout << columnLabels << endl;
	cout << rowDivider << endl;
	for (int i=1; i<9; i++) {
		cout << "\033[97;42m " << (i) << " \033[31;42m\u2502\033[m";
		for (int j=1; j<9; j++) {
			if (legalMoves[i][j] == 0) {
				cout << spaces[board[i][j]];
			}
			
			else if (legalMoves[i][j] < 10) {
				num = to_string(legalMoves[i][j]);
				cout << "\033[31;42m\u0020";
				cout << num;
				cout << "\u0020\033[31;42m\u2502\033[m";
			}
			
			else {
				num = to_string(legalMoves[i][j]);
				cout << "\033[31;42m\u0020";
				cout << num;
				cout << "\033[31;42m\u2502\033[m";
			}
		}
		cout << endl << rowDivider << endl;
	}
	
	return 1;
}


int othello::checkDirection(int i, int j, int di, int dj) {
	
    if (board[i+di][j+dj] != (3-turn)) { return 0; }
    else {i += di, j +=dj; }
    
    while(1) {
		if ( board[i+di][j+dj] == turn ) {
			return 1;
		}
		
		else if ( (board[i+di][i+dj] == 0) || (board[i+di][j+dj] == 3) ) {
			return 0;
		}
		
		else {
			i += di;
			j += dj;
		}
	}
}


int othello::flipTiles(int i0, int j0) {
    int i, j;
    board[i0][j0] = turn;
    for (int di : {-1,0,1}) {
		for (int dj : {-1,0,1}) {
            i = i0, j=j0;
			if (checkDirection(i, j, di, dj) == 1) {
				while (board[i+di][j+dj] != turn) {
					board[i+di][j+dj] = turn;
					i += di, j += dj;
				}
			}
		}
	}
	return 1;
}


int othello::findMoves() {
	
	int num = 0;
	
    // Reset legalMoves
    for (int i=1; i<9; i++) {
		for (int j=1; j<9; j++) {
			legalMoves[i][j] = 0;
        }
    }
    
    // Find all legal moves
	for (int i=1; i<9; i++) {
		for (int j=1; j<9; j++) {
			
			// If space isn't empty, check next space
			if (board[i][j] != 0) {
				continue;
			}
			
			// If space is empty, check for flippable tiles in each direction
			for (int di : {-1, 0, 1}) {
				for (int dj : {-1, 0, 1}) {
					
                    // Check if tiles can be flipped in that direction
                    if ( checkDirection(i, j, di, dj) == 1 ) {
                        legalMoves[i][j] = ++num;
                        goto nextSpace;
                    }
				}
			}
			nextSpace:;
		}
	}
	cout << "Number of moves: " << num << endl;
	return num;
}


int othello::doMove(int num) {
	for (int i=1; i<9; i++) {
		for (int j=1; j<9; j++) {
			if (legalMoves[i][j] == num) {
				flipTiles(i, j);
			}
		}
	}
    // Toggle turn and check if game is over
    turn = 3 - turn;
    if (findMoves() == 0) {
        turn = 3 - turn;
        cout << "No moves available. Skipping turn." << endl;
        if (findMoves() == 0) {
            cout << "No remaining moves. Goodbye." << endl;
            return 2;
        }
    }
	return 1;
}





int main() {
	
	// Test board to print
	int corner_test[8][8] = {
		{0,0,0,0,2,1,2,0},
		{0,0,0,0,0,2,1,2},
		{0,0,0,0,0,0,2,1},
		{0,0,0,0,0,0,0,2},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0}
	};
    
    int long_move[8][8] = {
		{0,0,2,2,2,1,2,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,1,2,1,1,1,0,0},
		{0,0,0,0,0,0,0,0},
		{0,1,2,1,1,1,0,0}
	};

	othello game = othello(long_move, 1);
	
	int move;
    string player;
    int state = 1;
	while(state == 1) {
		game.print();
		cout << (game.turn==1 ? "Black's turn" : "White's turn") << endl;
        cout << "Select a move: " << endl;
		cin >> move;
		state = game.doMove(move);
	}
    
    game.print();
	
	return 1;
}


