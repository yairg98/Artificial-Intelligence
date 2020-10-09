#include <iostream>
#include <windows.h>
#include <string>

using namespace std;

// Othello class
// Includes all othello-specific gameplay logic (e.g. - legal moves)
// Could be modified to inherit abstract 'game' class
class othello {
    
private:

    int board[8][8];
    int turn;
    int moves;
    
    
public:

    // Constructor for 'othello' class
    othello(int board[8][8] = { 0 }, int turn = 1, int moves = 0) {
        board = board;
        turn = turn;
        moves = moves;
    }
    
    
    void print() {
        
    }
    
};


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

    // Spaces[] stores strings to print for each type of board square
    // Each string is one board square and its right-hand divider
    string spaces[3];
    // Empty space - 3 space characters with a green background
    spaces[0] = "\033[97;42m\u0020\u0020\u0020\033[31;42m\u2502\033[m";
    // Black full block flanked by half blocks on a green background
    spaces[1] = "\033[30;42m\u2590\u2588\u258C\033[31;42m\u2502\033[m";
    // White full block flanked by half blocks on a green background
    spaces[2] = "\033[97;42m\u2590\u2588\u258C\033[31;42m\u2502\033[m";
    
    
    // rowDivider is printed between piece-rows to create the board grid
    string horizontal = "\033[31;42m\u2500\033[m";
    string intersection = "\033[31;42m\u253C\033[m";
    string divSpace = horizontal+horizontal+horizontal+intersection;
    string rowDivider;
    for (int i=0; i<9; i++) { rowDivider += divSpace; }
    
    
	// columnLabels is printed at the top of board
	string columnLabels = spaces[0];
	for (char i='A'; i<='H'; i++) {
		columnLabels += "\033[97;42m\u0020";
		columnLabels += string(1,i); // conversion not necessary
		columnLabels += "\u0020\033[31;42m\u2502\033[m";
	}
	
    
	// Print the board
	cout << columnLabels << endl;
	cout << rowDivider << endl;
	for (int i=0; i<8; i++) {
		cout << "\033[97;42m" << (i+1) << ": \033[31;42m\u2502\033[m";
		for (int j=0; j<8; j++) {
			cout << spaces[board[i][j]];
		}
		cout << endl << rowDivider << endl;
	}
	
    return 1;
}


