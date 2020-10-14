
#include <string>

using namespace std;

// Othello class
// Includes all othello-specific gameplay logic (e.g. - legal moves)
// Could be modified to inherit abstract 'game' class
class othello {
    
private:

	string rowDivider;
	string columnLabels;
    string spaces[3];
	
	
public:

    int board[10][10];
	int legalMoves[10][10] = { 0 };
    int turn; // 1 for black, 2 for white


    // Constructor for 'othello' class
	othello(int (&b)[8][8], int t=1);


	// Formats and prints board to standard output
	// Also identifies legal moves (numbered)
	int print();
	
	
	// Update the legal moves array
	// Returns the number of identified legal moves
	int findMoves();
	
	
	// Recursively checks for a sequence-ending piece
	// Return true if sequence implies a legal move, otherwise false
	int checkDirection(int i, int j, int di, int dj);
	
	
	// Place a tile at given space (i,j) and perform all necessary flips
	// Return 1 on success
	int flipTiles(int i, int j);
	
	
	// Execute the selected move
	// Return 1 if successful, otherwise return 0
	int doMove(int num);
	
	
};