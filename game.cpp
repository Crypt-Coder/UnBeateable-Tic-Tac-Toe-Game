#include "game.h"

/* Set the difficulty level accordingly
 * 1 is the easiest level (You can beat it easily)
 */
#define DIFFICULTY_LEVEL 5

// Declaration of functions to be used for playing this game
void performMove(class Board& board, int lvl, bool player);
int bestPossibleMove(class Board& board, int lvl, bool player, int *x, int *y);

// Driver Code
int main(int argc, char const *argv[])
{
	Board board;
	bool aiPlayer,humanPlayer;
	int lvl = DIFFICULTY_LEVEL,dec;
	cout << "Welcome to Tic-Tac-Toe\nWhat do you wish to play as:(1)X\t(2)O\n";
	cin >> dec;
	if(dec == 1) {
		aiPlayer = 0;
		humanPlayer = 1;	
	}
	else if (dec == 2) {
		aiPlayer = 1;
		humanPlayer = 0;
		performMove(board, lvl, aiPlayer);
	}
	else {
		cout <<"Invalid Value" << endl;
		return 0;
	}
	board.printBoard();
	while(board.checkVictory() == -1 && board.movesPossible()) {
		int x,y;
		cout << "Row:";
		cin >> x;
		cout << "Col:";
		cin >> y;
		if (x > 0 && x <= DIM_X && y > 0 && y <= DIM_Y)
			if (board.getVal(x,y) == NO_VAL)
				board.setVal(x,y,humanPlayer?X_VAL:O_VAL);
			else {
				cout << board.getVal(x,y) <<" Already present at that position\n";
				continue;
			}
		else {
			cout << "Please enter values b/w 1 and 3\n";
			continue;
		}
		if (board.checkVictory() == humanPlayer || !board.movesPossible()) {
			board.printBoard();
			break;
		}
		// AI's chance to play
		performMove(board, lvl, aiPlayer);
		board.printBoard();
	}
	dec = board.checkVictory();
	if (dec == humanPlayer)
		cout << "Congrats!! You have won the Game\n";
	else if (dec == aiPlayer)
		cout << "Oops!! You LOST\n";
	else
		cout << "Smart Play... But you can not beat me :)\n";
	return 0;
}

/* Plays for Computer 
 */
void performMove(class Board& board, int lvl, bool player) {
	
	int x,y;
	bestPossibleMove(board, lvl-1, player, &x, &y);

	// Plays the best possible move of Computer
	board.setVal(x,y,player?X_VAL:O_VAL);
	return;
}

/* Finds and returns the best possible move
 */
int bestPossibleMove(class Board& board, int lvl, bool player, int *x, int *y) {

	// Used to store the maximum and minimum value based on whether AI is Major or Minor player
	int mn = 1000, mx = -1000;
	int tx = 0, ty = 0, val = 0;
	for (int i = 1;i <= DIM_X; i++) {
		for (int j = 1;j <= DIM_Y; j++) {
			if (board.getVal(i, j) == NO_VAL) {
				// Temporarily add a value at position i,j
				board.setVal(i, j, player?X_VAL:O_VAL);
				if (board.checkVictory() == player) {
					*x = i;*y = j;
					board.setVal(i, j, NO_VAL);
					return player?1000:-1000;
				}
				// If analysis of children is required and if there still is a possible move
				if (lvl>0 && board.movesPossible())
					val = bestPossibleMove(board, lvl-1, !player, x, y);
				else
					// Our Heuristic -> (open win condition for max - open win condition for min)
					val = board.winConditionMaxPlayer() - board.winConditionMinPlayer();
				/* If Player is a major player then search for the maximum 
				 * possible value of our heuristic
				 */ 
				if (player == MAJOR_PLAYER && mx < val) {
					tx = i;ty = j;
					mx = val;
				}
				/* If player is a minor player then search for the minimum
				 * possible value of the heuristic
				 */
				else if (player == MINOR_PLAYER && mn > val) {
					tx = i;ty = j;
					mn = val;
				}
				// Remove the value added earlier
				board.setVal(i,j,NO_VAL);
			}
		}
	}
	/* Final co-ordinates of the position where the value is to be placed
	 * Note: The values are only required after the completion for the recursion call
	 * and when the control reaches back to the performMove() function 
	 */
	*x = tx;*y = ty;
	/* Return min or max value depending on the player the moves are calculated for
	 * Note: This value is used for taking decisions after completion of each
	 * recursion call 
	 */
	return player?mx:mn;
}