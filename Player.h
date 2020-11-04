#include <string>
#include <iostream>
#include <limits>
#include <time.h>
#include "board.h"
#include <chrono>
#include <thread>
#include <utility>

using namespace std;


// Player interface to choose game moves
class Player {

public:
	
	// Set player ID
	int id;
	
	Player(int n): id(n) {}
	
	// Selects and returns a move 
	virtual int getMove(othello &game) {
        return 0;
    }
	
};


// User-operated player
class Human: public Player {
	
public:

	Human(int n): Player(n) {}

	// Allow user to select a move
	int getMove(othello &game) {
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


// Selects moves at random
class Random: public Player {

public:

    Random(int n): Player(n) {
        srand(time(NULL));
    }

	int getMove(othello &game) {
        // Short pause to "think" - better playing experience
        cout << "Thinking..." << endl;
        // this_thread::sleep_for(chrono::seconds(1));
		return ( 1 + rand() % game.n_moves );
	}

};


// Basic bot - selects a move at random
class Bot: public Player {
	
private:
	// Set the player time limit
	chrono::seconds limit; // = chrono::seconds(2);

public:

	// Constructor for Bot - sets player ID and time limit (maybe chooses heuristic)
	Bot(int n): Player(n) {
		
		int lim = 0;
		bool valid= false;
		
		while (!valid) {
			cout << "Choose an time limit (in seconds) for PLAYER " << id << ": ";
			cin >> lim;
			
			if (cin.good()) { valid = true; }
			
			else {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(),'\n');
				cout << "Invalid input. Try again.\n" << endl;
			}
		}
		limit = chrono::seconds(lim);
	}

	// Prompt the player to make a move
	int getMove(othello &game);
	
	// Heuristic function
	int utility(othello &game);
	
	// Search a specific depth
	int searchDepth(othello &game, int depth);
	
	// Return the highest-value child move
	int maxVal(othello &game, int remaining);

	// Return the lowest-value child move
	int minVal(othello &game, int remaining);
	
};