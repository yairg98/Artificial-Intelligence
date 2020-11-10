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
		return ( 1 + rand() % game.curr_moves );
	}

};


// Performs Minimax search with Alpha-Beta pruning
// Currently uses basic piece-counting heuristic
class Bot: public Player {
	
private:
	
	// Set the player time limit
	chrono::seconds limit; // = chrono::seconds(2);
	
	// Board weights for strategic value
	int weights;

public:

	// Constructor for Bot - sets player ID and time limit (maybe chooses heuristic)
	Bot(int n): Player(n) {
		
		// Set up randomizer for use in the heuristic function
		srand(time(NULL));
		
		// Prompt user for the time limit in seconds
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
		// Set the time limit
		limit = chrono::seconds(lim);
	}

	// Prompt the player to make a move
	int getMove(othello &game);
	
	// Heuristic function
	double utility(othello &game);
	
	// Returns mobility metric for use in heuristic function
	inline int mobility(othello &game);
	
	// Returns difference in number of pieces on the board for use in heuristic function
	inline int pieces(othello &game);
	
	// Returns number of black corners minus number of white corners
	inline int corners(othello &game);
	
	// Search a specific depth
	int searchDepth(othello &game, int depth, chrono::steady_clock::time_point stopTime);
	
	// Return the highest-value child move
	double maxVal(othello &game, int depth, double alpha, double beta, chrono::steady_clock::time_point stopTime);

	// Return the lowest-value child move
	double minVal(othello &game, int depth, double alpha, double beta, chrono::steady_clock::time_point stopTime);
	
};


// Previous version of bot - for testing purposes
// Same as current version, but without pre-search move-ordering
class Bot2: public Player {
	
private:
	
	// Set the player time limit
	chrono::seconds limit; // = chrono::seconds(2);

public:

	// Constructor for Bot - sets player ID and time limit (maybe chooses heuristic)
	Bot2(int n): Player(n) {
		
		// Set up randomizer for use in the heuristic function
		srand(time(NULL));
		
		// Prompt user for the time limit in seconds
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
		// Set the time limit
		limit = chrono::seconds(lim);
	}

	// Prompt the player to make a move
	int getMove(othello &game);
	
	// Heuristic function
	double utility(othello &game);
	
	// Returns mobility metric for use in heuristic function
	int mobility(othello &game);
	
	// Returns difference in number of pieces on the board for use in heuristic function
	int pieces(othello &game);
	
	// Returns number of black corners minus number of white corners
	int corners(othello &game);
	
	// Search a specific depth
	int searchDepth(othello &game, int depth, chrono::steady_clock::time_point stopTime);
	
	// Return the highest-value child move
	double maxVal(othello &game, int depth, double alpha, double beta, chrono::steady_clock::time_point stopTime);

	// Return the lowest-value child move
	double minVal(othello &game, int depth, double alpha, double beta, chrono::steady_clock::time_point stopTime);
	
};