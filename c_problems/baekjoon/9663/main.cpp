#include <stdio.h>
#include <iostream>

using namespace std;

int N;
//column location of queen for each row
int queen[20];
int ans = 0;
//check impossible spot
int diag_impossible[20][20]; //diag_impossible could be accessed by several points, thus, if diag_impossible > 0, it means it is impossible, if == 0, it means it is possible
bool col_impossible[20];

int set_impossible(int mode, int coord_row, int coord_col)
{
	if(mode == 0) {
		col_impossible[coord_col] = false;			
		for(int i = coord_row; i < N; i++) {
			if((coord_col + i - coord_row) < N) {
				diag_impossible[i][coord_col + (i - coord_row)]--;
				if(diag_impossible[i][coord_col + i - coord_row] < 0) diag_impossible[i][coord_col + i - coord_row] = 0;
			}
			
			if((coord_col - i + coord_row) >= 0) {
				diag_impossible[i][coord_col - (i - coord_row)]--;
				if(diag_impossible[i][coord_col - i + coord_row] < 0) diag_impossible[i][coord_col - i + coord_row] = 0;
			}
		}
	}
	else if(mode == 1) {
		col_impossible[coord_col] = true;			
		for(int i = coord_row; i < N; i++) {
			if((coord_col + i - coord_row) < N) {
				diag_impossible[i][coord_col + (i - coord_row)]++;
			}
			
			if((coord_col - i + coord_row) >= 0) {
				diag_impossible[i][coord_col - (i - coord_row)]++;
			}
		}
	}

	return 0;
}

int queen_dfs(int cur_row)
{
	if(cur_row == N) {
		ans++;
#ifdef DEBUG
		for(int i = 0; i < N; i++) {
			cout << queen[i] << " ";
		}
		cout << endl;
#endif
		return 0;
	}		

	for(int i = 0; i < N; i++) {
		if((diag_impossible[cur_row][i] == 0) && !col_impossible[i]) {
			queen[cur_row] = i;
			set_impossible(1, cur_row, i);
			queen_dfs(cur_row + 1);
			set_impossible(0, cur_row, i);
		}
	}	
	
	return 0;
}

int main()
{
	cin >> N;

	for(int i = 0; i < N; i++) {
		for(int j = 0; j < N; j++) {
			diag_impossible[i][j] = false;
		}
		col_impossible[i] = false;
	}

	queen_dfs(0);			

	cout << ans << endl;

	return 0;
}
