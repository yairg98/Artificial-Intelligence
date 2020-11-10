#include <algorithm>
#include <cfloat>
#include "player.h"

using namespace std;


int Bot::getMove(othello &game) {

	cout << "Thinking..." << endl;

 	// Initialize timer variables
	chrono::steady_clock::time_point t1, t2, stopTime;
	chrono::duration<double> timeDiff;
	
	// Record the start-time (t1) and latest stop-time (stopTime) of the search
	t1 = chrono::steady_clock::now();
	stopTime = t1 + limit - chrono::milliseconds(1);
	
	// Initialize variables to track depth and best move
	int depth = 1, best = 0, next = 0;
	int maxDepth = 64 - (game.n_black + game.n_white);
	
	do {
		next = searchDepth(game, depth++, stopTime); // Get best move from next level
		if (next != 0) { best = next; } // next == 0 if the search ran out of time
		else { --depth; }
		t2 = chrono::steady_clock::now(); // Check the time
		timeDiff = chrono::duration_cast<chrono::duration<double>>(t2 - t1);
		//cout << timeDiff.count() << endl;
		
	} while ( (timeDiff < limit/2) && (depth <= maxDepth) );
	
	cout << timeDiff.count() << endl;
	
	// Search to specific depth (for testing)
	// int best = searchDepth(game, 2);
	cout << "Searched to depth: " << --depth << endl;
	cout << "Move selected: " << best << endl;
	return best;
	
}


double Bot::utility(othello &game) {
	
	double h = 0;
	
	h += pieces(game);
	h += mobility(game);
	// h += weights(game);
	
	// Add small random value to ensure equal moves are chosen between at random
	h += double(rand()) / RAND_MAX - 0.5;
	
	return h;
}


inline int Bot::mobility(othello &game) {
	int diff = (game.curr_moves - game.prev_moves);
	return game.turn==id ? diff : -diff;
}


inline int Bot::pieces(othello &game) {
	int diff = game.n_black - game.n_white;
	return id==1 ? diff : -diff; // Invert difference depending on the player
}


// inline int Bot::weights(othello &game) {
	// int net = 0;
	// for 
// }


int Bot::searchDepth(othello &game, int depth, chrono::steady_clock::time_point stopTime) {
	
	othello child = game; // Copy the current game configuration
	int n = game.curr_moves, state, best_move = 0;
	double best_score = - numeric_limits<double>::infinity(), score;
	
	// For each 1st-generation child
	for (int i = 1; i < n+1; i++) {
		
		// Check if we've run out of time
		if (chrono::steady_clock::now() >= stopTime) { return 0; }
		
		// Set the child equal to the parent, then execute the chosen move
		child = game;
		child.doMove(i);
		state = child.getState();
		
		// See below maxVal and minVal for line-specific comments on the following three lines
		if ( (state==0) || (depth==0) ) { score = utility(child); }
		else if (state != id) { score = minVal(child, depth-1, - numeric_limits<double>::infinity(), DBL_MAX, stopTime); }
		else { score = maxVal(child, depth-1, - numeric_limits<double>::infinity(), DBL_MAX, stopTime); }
		
		// Save the best move and its utility score
		if (score > best_score) {
			best_score = score;
			best_move = i;
		}
	}
	
	// Check the time again to make sure the level was searched to completion
	if (chrono::steady_clock::now() >= stopTime) { return 0; }
	
	return best_move;
}


double Bot::maxVal(othello &game, int d, double alpha, double beta, chrono::steady_clock::time_point stopTime) {
	
	othello child = game; // Copy the current game configuration
	int n = game.curr_moves, state;
	double best = - numeric_limits<double>::infinity(), v2;
	
	// Iterate through every legal move
	for (int i=1; i<n+1; i++) {
		
		// Check if we've run out of time
		if (chrono::steady_clock::now() >= stopTime) { return - numeric_limits<double>::infinity(); }
		
		// Set the child equal to the parent, then execute the chosen move
		child = game;
		child.doMove(i);
		state = child.getState();
		
		// Check if game is over or has reached the maximum depth
		if ( (state==0) || (d==0) ) { v2 = utility(child); }
		// Switch to minVal if it's the other player's turn
		else if (state != id) { v2 = minVal(child, d-1, alpha, beta, stopTime); }
		// Run maxVal again if the opponents turn was skipped
		else { v2 = maxVal(child, d-1, alpha, beta, stopTime); }
		
		// Check for new max-value move
		if (v2 > best) {
			best = v2;
			alpha = max(alpha, best);
		}
		
		// Alpha-Beta pruning addition
		if (best >= beta) { return best; }
	}
	
	// Check the time again to make sure the level was searched to completion
	if (chrono::steady_clock::now() >= stopTime) { return - numeric_limits<double>::infinity(); }
	
	return best;
}


double Bot::minVal(othello &game, int d, double alpha, double beta, chrono::steady_clock::time_point stopTime) {
	
	othello child = game; // Copy the current game configuration
	int n = game.curr_moves, state;
	double best = DBL_MAX, v2;
	
	// Iterate through every legal move
	for (int i=1; i<n+1; i++) {
		
		// Check if we've run out of time
		if (chrono::steady_clock::now() >= stopTime) { return DBL_MAX; }
		
		// Set the child equal to the parent, then execute the chosen move
		child = game;
		child.doMove(i);
		state = child.getState();
		
		// Check if game is over or has reached the maximum depth
		if ( (state==0) || (d==0) ) { v2 = utility(child); }
		// Switch to minVal if it's the other player's turn
		else if (state != id) { v2 = minVal(child, d-1, alpha, beta, stopTime); }
		// Run maxVal again if the opponents turn was skipped
		else { v2 = maxVal(child, d-1, alpha, beta, stopTime); }
		
		// Check for new min-value move
		if (v2 < best) {
			best = min(best, v2);
			beta = min(beta, best);
		}
		
		// Alpha-Beta pruning addition
		if (best <= alpha) { return best; }
	}
	
	// Check the time again to make sure the level was searched to completion
	if (chrono::steady_clock::now() >= stopTime) { return DBL_MAX; }
	
	return best;
}