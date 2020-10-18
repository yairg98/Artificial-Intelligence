#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include "Player.h"

using namespace std;


// Loads and returns the gameboard (based on user selection)
Othello loadBoard() {
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
        return Othello(board_0, 1);
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
        return Othello(board_0, turn);
    }
    
    else {
        cout << "Invalid entry. Try again." << endl;
        goto top;
    }
    
}


// Creates and returns a player of the correct type (based on user selection)
int getPlayer(int p) {
	top:;
	int type;
	cout << "Choose a type for PLAYER " << p << ":" << endl;
	cout << "1. Human" << endl;
	cout << "2. Random-selector bot" << endl;
	cin >> type;
	if ( !cin.good() ) { goto top; }
    
	else if (type == 1) { return 1; }
	else if (type == 2) { return 2; }
    
	else {goto top; }
}



// Runs the game
int main() {
	
	// Select players (human, AI, random, etc.)
	// players[0] is left empty to keep the index consistent with the player id
	vector<unique_ptr<Player>> players;
    int type;
	for ( int i : {1, 2} ) {
        type = getPlayer(i);
        if (type == 1) { players.emplace_back( new Human() ); }
        else if (type == 2) { players.emplace_back( new Random() ); }
	}
    
	// Load and start the game
    Othello game = loadBoard();
	int state = game.getState(1); // 1 or 2 for turn, or 0 for game over
    
    // Continue making moves until the game ends
    int move;
    int legal;
	while(state != 0) {
		game.print();
		legal = 0;
        cout << "PLAYER " << game.turn << endl;
        while (legal == 0) {
			move = players[state-1]->getMove(game);
            legal = game.doMove(move);
        }
        state = game.getState();
	}
    
    game.print();
    game.score();
    
	return 1;
}