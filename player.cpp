#include <algorithm>
#include <climits>
#include "player.h"

using namespace std;


int Bot::getMove(othello &game) {

	// Initialize timer variables
	chrono::steady_clock::time_point t1, t2;
	chrono::duration<double> timeDiff;
	
	// Record the start time of the search (t1)
	t1 = chrono::steady_clock::now();
	
	// Initialize variables to track depth and best move
	int depth = 1, best, next;
	
	// do {
		// next = searchDepth(game, depth++); // Get best move from next level
		// if (next != 0) { best = next; } // next == 0 if the search ran out of time
		// t2 = chrono::steady_clock::now(); // Check the time
		// timeDiff = chrono::duration_cast<chrono::duration<double>>(t2 - t1);
	// } while (timeDiff < limit/2);

	best = searchDepth(game, 1);
	
	return best;
	
}


int Bot::utility(othello &game) {
	
	int diff = game.n_black - game.n_white;
	if (game.turn == 1) { return diff; }
	else { return 0-diff; }
}


int Bot::searchDepth(othello &game, int depth) {
	return maxVal(game, depth).first;
}


pair<int, int> Bot::maxVal(othello &game, int d) {
	
	othello child = game; // Copy the current game configuration
	int n = game.n_moves; // Number of possible moves from teh current configuration
	int values[n];
	int state;
	for (int i=1; i<n+1; i++) {
		child = game;
		child.doMove(i);
		child.print();
		state = child.getState();
		if ( (state==0) || (d==0) ) { values[i-1] = utility(child); }
		else if (state != game.turn) { values[i-1] = minVal(child, d-1).second; }
		else { values[i-1] = maxVal(child, d-1).second; }
	}
	
	pair<int, int> best;
	best.first = 0;
	best.second = INT_MIN;
	for (int i=1; i<n+1; i++) {
		if (values[i-1] > best.second) {
			best.first = i;
			best.second = values[i-1];
		}
	}
	
	cout << "MAX: (d = " << d << ")" << endl;
	for (int i : values) { cout << i << ", "; }
	cout << endl;
	
	return best;
}


pair<int, int> Bot::minVal(othello &game, int d) {
	
	othello child = game;
	
	
	int n = game.n_moves;
	int values[n];
	int state;
	for (int i=0; i<n; i++) {
		child = game;
		child.doMove(i);
		state = child.getState();
		if ( (state==0) || (d==0) ) { values[i-1] = utility(child); }
		else if (state != game.turn) { values[i-1] = maxVal(child, d-1).second; }
		else { values[i-1] = minVal(child, d-1).second; }
	}
	
	pair<int, int> best;
	best.first = 0;
	best.second = INT_MIN;
	for (int i=1; i<n+1; i++) {
		if (values[i-1] > best.second) {
			best.first = i;
			best.second = values[i-1];
		}
	}
	
	cout << "MIN: (d = " << d << ")" << endl;
	for (int i : values) { cout << i << ", "; }
	cout << endl;
	
	return best;
}