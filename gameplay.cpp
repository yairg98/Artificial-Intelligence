#include <string>
#include <iostream>
#include <fstream>
#include "othello.h"

using namespace std;


int main() {
	
	// Test board to print
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

	othello game(corner_test, 1);
	
	int move;
    string player;
    int state = 1;
	while(state == 1) {
		game.print();
		cout << (game.turn==1 ? "Black's turn" : "White's turn") << endl;
        cout << "Select a move: " << endl;
		cin >> move;
		state = game.doMove(move);
	}
    
    game.print();
	
	return 1;
}