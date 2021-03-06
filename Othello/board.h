
#include <string>

using namespace std;

// othello class
// Includes all othello-specific gameplay logic (e.g. - legal moves)
// Could be modified to inherit abstract 'game' class
class othello {
    
public:

    int board[10][10];
	int legalMoves[10][10] = { 0 };
	int coords[64][2];
	int curr_moves; // number of legal moves available
	int prev_moves; // Number of moves available during previous turn (for implementing zero-sum heuristic)
	int n_black; // number of pieces - player 1
	int n_white; // number of pieces - player 2
    int turn; // 1 for black, 2 for white


    // Constructor for 'othello' class
	othello(int (&b)[8][8], int t=1);


	// Formats and prints board to standard output
	// Also identifies legal moves (numbered)
	int print();
	
	
	// Execute the selected move
	// Return 1 if successful, otherwise return 0
	int doMove(int num);
    
	
    // Check the state of the board and set turn accordingly
    // Return 0 for regular turn; 1 for skipped turn; 2 for game over
    int getState(int firstMove = 0);
    
	
    // Calculate and print the final score
    // Return the winning player, or 0 for a draw
    int score();
	
	
private:

	string rowDivider;
	string columnLabels;
    string spaces[3];
	
		
	// Recursively checks for a sequence-ending piece
	// Return true if sequence implies a legal move, otherwise false
	int checkDirection(int i, int j, int di, int dj);
	
	
	// Place a tile at given space (i,j) and perform all necessary flips
	// Return 1 on success
	int flipTiles(int i, int j);
	
	
	// Update the legal moves array
	// Returns the number of identified legal moves
	int update();
	
	
};
