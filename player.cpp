#include <algorithm>
#include <climits>
#include "player.h"

using namespace std;


int Bot::getMove(othello &game) {

	return searchDepth(game, 3);
}


int Bot::utility(othello &game) {
	int diff = game.n_black - game.n_white;
	if (game.turn = 1) { return diff; }
	else { return -diff; }
}


int Bot::searchDepth(othello &game, int depth) {
	return maxVal(game, depth).first;
}


pair<int, int> Bot::maxVal(othello &game, int d) {
	
	othello child = game;
	int n = game.n_moves;
	int values[n];
	int state;
	for (int i=1; i<n+1; i++) {
		child = game;
		child.doMove(i);
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
	best.second = INT_MAX;
	for (int i=1; i<n+1; i++) {
		if (values[i-1] > best.second) {
			best.first = i;
			best.second = values[i-1];
		}
	}
	
	return best;
}