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

    string div = "\033[30;42m\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\033[32;40m";
    string row = "\033[32;40m\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588";
    
    for (int i=0; i<4; i++) {
        cout << row << endl;
        cout << div << endl;
    }
    
    // cout << "\033[32;40m\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588";
    // cout << "\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588" << endl; // full block
    
    // cout << "\033[30;42m\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500";
    // cout << "\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\033[32;40m" << endl;
    
    // cout << "\033[32;40m\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588";
    // cout << "\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588" << endl; // full block
    
    // cout << "\033[30;42m\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500";
    // cout << "\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\033[32;40m" << endl;
    
    // cout << "\033[32;40m\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588";
    // cout << "\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588" << endl; // full block
    
    // cout << "\033[30;42m\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500";
    // cout << "\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2500\033[m" << endl;
    
    // cout << "\033[32;40m\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588";
    // cout << "\u2588\u2588\u2588\u2588\u2588\u2588\u2588\u2588" << endl; // full block
    
    return 1;
}


