#include <string>
#include <iostream>
#include <fstream>
#include "othello.h"

using namespace std;


int main() {
	
	// Test board to print
	int def_board[8][8] = {
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,1,2,0,0,0},
		{0,0,0,2,1,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0}
	};
    
    int corner_test[8][8] = {
		{0,0,0,0,2,1,2,0},
		{0,0,0,0,0,2,1,2},
		{0,0,0,0,0,0,2,1},
		{0,0,0,0,0,0,0,2},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0}
	};

	othello game(def_board, 1);
	
	int move;
    int state = 1;
	while(state == 1) {
		game.print();
		cout << "PLAYER " << game.turn << endl;
        cout << "Select a move: " << endl;
		cin >> move;
		state = game.doMove(move);
	}
    
    game.print();
	
	return 1;
}