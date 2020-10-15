#include "othello.h"
#include <windows.h>
#include <string>
#include <iostream>

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
		
		else if ( (board[i+di][j+dj] == 0) || (board[i+di][j+dj] == 3) ) {
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
    return 1;
}


int othello::getState(int firstMove) {
    cout << endl;
    // Unless it's the first move, toggle turn
    if (!firstMove) {
        turn = 3 - turn;
    }
    // Check for available moves, and toggle turn as necessary
    if (findMoves() == 0) {
        turn = 3 - turn;
        // If no moves are available for either player (game is over)
        if (findMoves() == 0) {
            cout << "No moves remaining. Game has ended." << endl;
            return 2;
        }
        // If a turn was skipped but the game is not over
        else {
            cout << "Skipped a turn because no moves were available." << endl;
            return 1;
        }
    }
	// If moves are available and turn changes normally
    return 0;
}


int othello::score() {
    int black = 0;
    int white = 0;
    
    // Count up the pieces
    for (int i=1; i<9; i++) {
        for (int j=1; j<9; j++) {
            if (board[i][j] == 1) { black++; }
            else if (board[i][j] == 2) { white++; }
        }
    }
    
    // Identify the winner
    int winner;
    if (black > white) { winner = 1; }
    else if (white > black) { winner = 2; }
    else { winner = 0; }
    
    // Print message
    cout << "Final Score:" << endl;
    cout << "  Black: " << black << endl;
    cout << "  White: " << white << endl;
    cout << endl;
    if (winner == 0) { cout << "Match is a draw!" << endl; }
    else { cout << "Winner is PLAYER " << winner << "!" << endl; }
    
    return winner;
}


