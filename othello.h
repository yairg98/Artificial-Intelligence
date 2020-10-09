
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
	string rowDivider;
	string columnLabels;
    string spaces[3];
	
	
public:

    // Constructor for 'othello' class
    othello(int board[8][8] = { 0 }, int turn = 1, int moves = 0);


	// Formats and prints board to standard output
	int print(int [8][8]);


	

};