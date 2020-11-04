#include <algorithm>
#include <climits>
#include "player.h"

using namespace std;


int Bot::getMove(othello &game) {

	/* // Initialize timer variables
	chrono::steady_clock::time_point t1, t2;
	chrono::duration<double> timeDiff;
	
	// Record the start time of the search (t1)
	t1 = chrono::steady_clock::now();
	
	// Initialize variables to track depth and best move
	int depth = 1, best, next;
	
	do {
		next = searchDepth(game, depth++); // Get best move from next level
		if (next != 0) { best = next; } // next == 0 if the search ran out of time
		t2 = chrono::steady_clock::now(); // Check the time
		timeDiff = chrono::duration_cast<chrono::duration<double>>(t2 - t1);
	} while (timeDiff < limit/2); */

	int best = searchDepth(game, 2);
	
	return best;
	
}


int Bot::utility(othello &game) {
	
	int diff = game.n_black - game.n_white; // Subtract PLAYER 2 pieces from PLAYER 1 pieces
	if (id == 1) { return diff; } // Return positive for PLAYER 1 heuristic
	else if (id==2) { return diff; } // Return negative for PLAYER 2 heuristic
	
	return 0; // Should never happen
}


int Bot::searchDepth(othello &game, int depth) {
	
	othello child = game; // Copy the current game configuration
	int n = game.n_moves; // Number of possible moves from teh current configuration
	int values[n];
	int state;
	int best_move = 0;
	int best_score = INT_MIN;
	int score;
	
	// For each 1st-generation child move
	for (int i = 1; i < game.n_moves+1; i++) {
		
		// Set the child equal to the parent, then execute the chosen move
		child = game;
		child.doMove(i);
		state = child.getState();
		
		// Check the move's overall depth-utility
		if ( (state==0) || (depth==0) ) { score = utility(child); }
		else if (state != id) { score = minVal(child, depth-1); }
		else { score = maxVal(child, depth-1); }
		
		// Save the best move and its utility score
		if (score > best_score) {
			best_score = score;
			best_move = i;
		}
	}
		
	return best_move;
}


int Bot::maxVal(othello &game, int d) {
	
	othello child = game;
	int n = game.n_moves, best = INT_MIN, state;
	int values[n];
	
	// Iterate through every legal move
	for (int i=1; i<n+1; i++) {
		
		// Set the child equal to the parent, then execute the chosen move
		child = game;
		child.doMove(i);
		state = child.getState();
		
		// Check if game is over or has reached the maximum depth
		if ( (state==0) || (d==0) ) { values[i-1] = utility(child); }
		
		// Switch to minVal if it's the other player's turn
		else if (state != id) { values[i-1] = minVal(child, d-1); }
		
		// Run maxVal again if the opponents turn was skipped
		else { values[i-1] = maxVal(child, d-1); }
		
		best = max(best, values[i-1]);
	}
	
	// ****************************************************************
	cout << "MAX: (d = " << d << ")" << endl;
	for (int i : values) { cout << i << ", "; }
	cout << endl;
	
	return best;
}


int Bot::minVal(othello &game, int d) {
	
	othello child = game; // Copy the current game configuration
	int n = game.n_moves, best = INT_MAX, state, v2;
	
	// Iterate through every legal move
	for (int i=1; i<n+1; i++) {
		
		// Set the child equal to the parent, then execute the chosen move
		child = game;
		child.doMove(i);
		state = child.getState();
		
		// Check if game is over or has reached the maximum depth
		if ( (state==0) || (d==0) ) { v2 = utility(child); }
		
		// Switch to minVal if it's the other player's turn
		else if (state != id) { v2 = maxVal(child, d-1); }
		
		// Run maxVal again if the opponents turn was skipped
		else { v2 = minVal(child, d-1); }
		
		best = min(best, v2);
	}
	
	return best;
}