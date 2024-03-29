#include "board.h"
// #include <windows.h>
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
	
	// Set the order in which potential moves should be checked
	int x=0, i, j;
	int typo_coords[16][2] = { {1,1}, {3,3}, {1,3}, {3,1}, {1,4}, {4,1},
	{3,4}, {4,3}, {4,4}, {2,4}, {4,2}, {2,3}, {3,2}, {1,2}, {2,1}, {2,2} };
	
	for (int y=0; y<16; y++) {
		// Set i and j for upper left corner
		i = typo_coords[y][0];
		j = typo_coords[y][1];
		
		// Add coordinates [i,j] and corresponding symmetric points
		coords[x][0] = i;
		coords[x][1] = j;
		x++;
		coords[x][0] = i;
		coords[x][1] = 9-j;
		x++;
		coords[x][0] = 9-i;
		coords[x][1] = j;
		x++;
		coords[x][0] = 9-i;
		coords[x][1] = 9-j;
		x++;
	}	
	
	// Set initial legal moves
	update();
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
		if ( board[i+di][j+dj] == turn ) { return 1; }
		else if ((board[i+di][j+dj] == 0)||(board[i+di][j+dj] == 3)) { return 0; }
		else { i += di, j += dj; }
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


int othello::update() {
	
	prev_moves = curr_moves;
	curr_moves = 0;
	n_black = 0;
	n_white = 0;
	
    // Reset legalMoves and count black and white pieces
	for (int i=1; i<9; i++) {
		for (int j=1; j<9; j++) {
			legalMoves[i][j] = 0;
			if (board[i][j]==1) { n_black++; }
			else if (board[i][j]==2) { n_white++; }
        }
    }
    
    // Find all legal moves
	int i, j;
	for (int x=0; x<64; x++) {
		
		i = coords[x][0];
		j = coords[x][1];
			
		// If space isn't empty, check next space
		if (board[i][j] != 0) {
			continue;
		}
		
		// If space is empty, check for flippable tiles in each direction
		for (int di : {-1, 0, 1}) {
			for (int dj : {-1, 0, 1}) {
				
				// Check if tiles can be flipped in that direction
				if ( checkDirection(i, j, di, dj) == 1 ) {
					legalMoves[i][j] = ++curr_moves;
					goto nextSpace;
				}
			}
		}
		nextSpace:;
	}
	return curr_moves;
}


int othello::doMove(int num) {
	if (num == 0) {return 0; }
	for (int i=1; i<9; i++) {
		for (int j=1; j<9; j++) {
			if (legalMoves[i][j] == num) {
				flipTiles(i, j);
                return 1;
			}
		}
	}
    return 0;
}


int othello::getState(int firstMove) {
    // Unless it's the first move, toggle turn
    if (!firstMove) {
        turn = 3 - turn;
    }
    // Check for available moves, and toggle turn as necessary
    if (update() == 0) {
        turn = 3 - turn;
        // If no moves are available for either player (game is over)
        if (update() == 0) {
            return 0;
        }
        // If a turn was skipped but the game is not over
        else {
            return turn;
        }
    }
	// If moves are available and turn changes normally
    return turn;
}


int othello::score() {
    
    // Identify the winner
    int winner;
    if (n_black > n_white) { winner = 1; }
    else if (n_white > n_black) { winner = 2; }
    else { winner = 0; }
    
    // Print message
    cout << "Final Score:" << endl;
    cout << "  Black: " << n_black << endl;
    cout << "  White: " << n_white << endl;
    cout << endl;
    if (winner == 0) { cout << "Match is a draw!" << endl; }
    else { cout << "Winner is PLAYER " << winner << "!" << endl; }
    
    return winner;
}


