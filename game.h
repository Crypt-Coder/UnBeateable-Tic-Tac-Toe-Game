#include <bits/stdc++.h>
using namespace std;
#define NO_VAL ' '
#define O_VAL 'O'
#define X_VAL 'X'
#define DIM_X 3
#define DIM_Y 3
#define K 3					// Currently not in use
#define MAJOR_PLAYER 1
#define MINOR_PLAYER 0


// Board to be used for playing TIC-TAC-TOE
class Board {
private:
	char b[DIM_X][DIM_Y];
public:
	// Initialize the Board with blanks
	Board() {
		for (int i = 0;i < DIM_X; i++) {
			for (int j = 0;j < DIM_Y; j++) {
				b[i][j] = NO_VAL;
			}
		}
	}
	void setVal(int x, int y, char val) {
		b[x-1][y-1] = val;
	}
	char getVal(int x, int y) {
		return b[x-1][y-1];
	}
	int checkVictory() {
		// X -> 1, O -> 0
		int cntmajor = 0, cntminor = 0;
		for (int i = 0;i < DIM_X; i++) {
			int cnt = 0, cnt1 = 0;
			for (int j = 0;j < DIM_Y; j++) {
				//Horizontal Check
				if (b[i][j] == X_VAL)						cnt++;
				else if (b[i][j] == O_VAL)					cnt--;

				//Vertical Check
				if (b[j][i] == X_VAL)						cnt1++;
				else if (b[j][i] == O_VAL)					cnt1--;

				//Major Diagonal Check
				if (i==j && b[i][j] == X_VAL)				cntmajor++;
				else if (i==j && b[i][j] == O_VAL)			cntmajor--;

				// Minor Diagonal Check
				if (i+j == DIM_X-1 && b[i][j] == X_VAL)		cntminor++;
				else if (i+j == DIM_X-1 && b[i][j] == O_VAL)cntminor--;
			}
			// cnt == DIM_Y i.e the all 'X' found on that row
			if (cnt  ==  DIM_Y)	return 1;
			if (cnt  == -DIM_Y)	return 0;
			if (cnt1 ==  DIM_X)	return 1;
			if (cnt1 == -DIM_X)	return 0;
		}
		if (DIM_X == DIM_Y && cntmajor == DIM_X)		return 1;
		else if (DIM_X == DIM_Y && cntmajor == -DIM_X)	return 0;

		if (DIM_X == DIM_Y && cntminor == DIM_X)		return 1;
		else if (DIM_X == DIM_Y && cntminor == -DIM_X)	return 0;
		return -1;
	}
	/* Determine if there is a possible move left
	 * If possible -> True	
	 * Else -> False
	 */
	bool movesPossible() {
		for(int i = 0;i < DIM_X;i++)
			for (int j = 0;j < DIM_Y;j++)
				if (b[i][j] == NO_VAL)
					return 1;
		return 0;
	}
	/* Check win conditions for MAX player i.e. 'X'
	 */
	int winConditionMaxPlayer() {
		int total_cnt = 0;
		int cntmajor = 0, cntminor = 0;
		int flagmajor = 0, flagminor = 0;
		for (int i = 0;i < DIM_X; i++) {
			int cnt = 0, cnt1 = 0;
			int flag = 0, flag1 = 0;
			for (int j = 0;j < DIM_Y; j++) {
				//Horizontal Check
				if (b[i][j] == X_VAL)		{cnt++;flag++;}
				else if (b[i][j] == O_VAL)	cnt = -DIM_X;
				else if (b[i][j] == NO_VAL)	cnt++;

				//Vertical Check
				if (b[j][i] == X_VAL)		{cnt1++;flag1++;}
				else if (b[j][i] == O_VAL)	cnt1 = -DIM_Y;
				else if (b[j][i] == NO_VAL)	cnt1++;

				//Major Diagonal Check
				if (i==j && b[i][j] == X_VAL)				 {cntmajor++;flagmajor++;}
				else if (i==j && b[i][j] == O_VAL)			 cntmajor = -DIM_X;
				else if (i==j && b[i][j] == NO_VAL)			 cntmajor++;

				// Minor Diagonal Check
				if (i+j == DIM_X-1 && b[i][j] == X_VAL)		 {cntminor++;flagminor++;}
				else if (i+j == DIM_X-1 && b[i][j] == O_VAL) cntminor = -DIM_X;
				else if (i+j == DIM_X-1 && b[i][j] == NO_VAL)cntminor++;
			}
			if (cnt == DIM_Y && flag == DIM_Y-1)	total_cnt+=10;
			else if (cnt == DIM_Y && flag)  	    total_cnt++;
			if (cnt1 == DIM_X && flag1 == DIM_X-1)	total_cnt+=10;
			else if (cnt1 == DIM_X && flag1) 		total_cnt++;
		}
		if (DIM_X == DIM_Y && cntmajor == DIM_X && flagmajor == DIM_X-1)	total_cnt+=10;
		else if (DIM_X == DIM_Y && cntmajor == DIM_X && flagmajor)			total_cnt++;
		if (DIM_X == DIM_Y && cntminor == DIM_X && flagminor == DIM_X-1)	total_cnt+=10;
		else if (DIM_X == DIM_Y && cntminor == DIM_X && flagminor)			total_cnt++;
		
		return total_cnt;
	}
	/* Check win conditions for MIN player i.e. 'O'
	 */
	int winConditionMinPlayer() {
		int total_cnt = 0;
		int cntmajor = 0, cntminor = 0;
		int flagmajor = 0, flagminor = 0;
		for (int i = 0;i < DIM_X; i++) {
			int cnt = 0, cnt1 = 0;
			int flag = 0, flag1 = 0;
			for (int j = 0;j < DIM_Y; j++) {
				//Horizontal Check
				if (b[i][j] == O_VAL)		{cnt++;flag++;}
				else if (b[i][j] == X_VAL)	cnt = -DIM_X;
				else if (b[i][j] == NO_VAL)	cnt++;

				//Vertical Check
				if (b[j][i] == O_VAL)		{cnt1++;flag1++;}
				else if (b[j][i] == X_VAL)	cnt1 = -DIM_Y;
				else if (b[j][i] == NO_VAL)	cnt1++;

				//Major Diagonal Check
				if (i==j && b[i][j] == O_VAL)				 {cntmajor++;flagmajor++;}
				else if (i==j && b[i][j] == X_VAL)			 cntmajor = -DIM_X;
				else if (i==j && b[i][j] == NO_VAL)			 cntmajor++;

				// Minor Diagonal Check
				if (i+j == DIM_X-1 && b[i][j] == O_VAL)		 {cntminor++;flagminor++;}
				else if (i+j == DIM_X-1 && b[i][j] == X_VAL) cntminor = -DIM_X;
				else if (i+j == DIM_X-1 && b[i][j] == NO_VAL)cntminor++;
			}
			if (cnt == DIM_Y && flag == DIM_Y-1)	total_cnt+=10;
			else if (cnt == DIM_Y && flag)  	    total_cnt++;
			if (cnt1 == DIM_X && flag1 == DIM_X-1)	total_cnt+=10;
			else if (cnt1 == DIM_X && flag1) 		total_cnt++;
		}
		if (DIM_X == DIM_Y && cntmajor == DIM_X && flagmajor == DIM_X-1)	total_cnt+=10;
		else if (DIM_X == DIM_Y && cntmajor == DIM_X && flagmajor)			total_cnt++;
		if (DIM_X == DIM_Y && cntminor == DIM_X && flagminor == DIM_X-1)	total_cnt+=10;
		else if (DIM_X == DIM_Y && cntminor == DIM_X && flagminor)			total_cnt++;
		return total_cnt;
	}
	/* Print the board in a proper format
	 */
	void printBoard() {
		for(int i = 1;i <= DIM_X; i++) {
			for(int j = 1;j <= DIM_Y; j++) {
				cout << getVal(i,j);
				if (j != DIM_Y)		cout << "|";
			}
			cout << endl;
		}
	}
};