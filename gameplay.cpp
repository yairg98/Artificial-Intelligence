#include <string>
#include <iostream>
#include <fstream>
#include "othello.h"

using namespace std;

othello loadBoard() {
    top:;
    string input;
    // Optionally load  board position from a text file
    cout << "\nWould you like to:" << endl;
    cout << "1. Start a new game" << endl;
    cout << "2. Load a board position from a text file" << endl;
    cout << "-> ";
    cin >> input;
    
    // Load default staring board
    if (input == "1") {
        int board_0[8][8] = {
            {0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0},
            {0,0,0,1,2,0,0,0},
            {0,0,0,2,1,0,0,0},
            {0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0}
        };
        return othello(board_0, 1);
    }
    
    else if (input == "2") {
        int board_0[8][8];
        cout << "\nEnter the file name: "<< endl;
        cout << "-> ";
        cin >> input;
        ifstream fp(input);
        if (! fp) {
            cout << "Error, file couldn't be opened" << endl; 
            goto top;
        }
        for(int row = 0; row < 8; row++) {
           for(int col = 0; col < 8; col++){
                fp >> board_0[row][col];
                if ( ! fp ) {
                   cout << "Error reading file for element " << row << "," << col << endl; 
                   goto top;
                }
            }
        }
        int turn;
        fp >> turn; // make sure this is 1 0r 2
        return othello(board_0, turn);
    }
    
    else {
        cout << "Invalid entry. Try again." << endl;
        goto top;
    }
    
}


int main() {
	
    othello game = loadBoard();
	int state = game.getState(1);
    
    // Continue making moves until the game ends
    int move;
    int legal;
	while(state != 0) {
		game.print();
		legal = 0;
        cout << "PLAYER " << game.turn << endl;
        cout << "Select a move: " << endl;
        while (legal == 0) {
            cout << "-> ";
            cin >> move;
            legal = game.doMove(move);
        }
        state = game.getState();
	}
    
    game.print();
    game.score();
    
	return 1;
}