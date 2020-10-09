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

    // cout << "\u2B24\u2B24\u2B24" << endl; // solid circle
    // cout << "\033[1;31m\u2B24\u2B24\033[92;105m\u2B24\033[m\n" << endl; // solid circle
    
    string spaces[3];
    
    return 1;
}


