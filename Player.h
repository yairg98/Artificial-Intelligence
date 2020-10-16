#include <string>
#include <iostream>
#include <limits>
#include <time.h>
#include "Othello.h"

using namespace std;


// Player interface to choose game moves
class Player {

public:
    
	// Selects and returns a move 
	virtual int getMove(Othello &game) {
        return 0;
    }
	
};


// User-operated player
class Human: public Player {
	
public:

	// Allow user to select a move
	int getMove(Othello &game) {
		int move = 0;
		bool valid= false;
		
		while (!valid) {
			cout << "Select a move: " << endl;
			cout << "-> ";
			cin >> move;
			
			if (cin.good()) { valid = true; }
			
			else {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(),'\n');
				cout << "Invalid input. Try again.\n" << endl;
			}
		}
		return move;
	}
	
};


// Basic bot - selects a move at random
class Random: public Player {

public:

	int getMove(Othello &game) {
        srand(time(NULL));
		return ( 1 + rand() % game.n_moves );
	}

};
