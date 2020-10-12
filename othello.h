
#include <string>

using namespace std;

// Othello class
// Includes all othello-specific gameplay logic (e.g. - legal moves)
// Could be modified to inherit abstract 'game' class
class othello {
    
private:

    int board[10][10];
	int legalMoves[8][8];
    int turn; // 1 for black, 2 for white
    int moves;
	string rowDivider;
	string columnLabels;
    string spaces[3];
	
	
public:

    // Constructor for 'othello' class
    //othello(int board[8][8] = { 0 }, int turn = 1, int moves = 0);
	othello(int (&b)[8][8], int t=0, int m=0);


	// Formats and prints board to standard output
	int print();
	
	
	// Update the legal moves array
	int findMoves();
	
	
};