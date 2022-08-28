#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <vector>

using namespace std;

int N;
int home[20][20];

//cache[a-1][b-1][c] : the number of paths from (a, b) to (N, N) when pipe direction is c to (a, b)
int cache[20][20][3];

//pipe_dir : latest state is horizontal : 0, vertical : 1, diagonal : 2
int find_paths(int pipe_dir, int row, int col)
{
	if((row == (N - 1)) && (col == (N - 1))) {
		//at the end
		return 1;
	}	
	else {
		//check visited and initialization for counting
		cache[row][col][pipe_dir] = 0;
		if((pipe_dir == 0) && (home[row][col + 1] == 0)) {
			//move horizontally available
			if(cache[row][col + 1][0] == -1) {
				find_paths(0, row, col + 1);	
				cache[row][col][pipe_dir] += cache[row][col + 1][0];
			}	
			else {
				cache[row][col][pipe_dir] += cache[row][col + 1][0];
			}
			
			if((home[row + 1][col + 1] == 0) && (home[row + 1][col] == 0)) {
				//move diagonally available
				if(cache[row + 1][col + 1][2] == -1) {
					find_paths(2, row + 1, col + 1);	
					cache[row][col][pipe_dir] += cache[row + 1][col + 1][2];
				}	
				else {
					cache[row][col][pipe_dir] += cache[row + 1][col + 1][2];
				}
			}
		}

		if((pipe_dir == 1) && (home[row + 1][col] == 0)) {
			//move vertically available
			if(cache[row + 1][col][1] == -1) {
				find_paths(1, row + 1, col);	
				cache[row][col][pipe_dir] += cache[row + 1][col][1];
			}	
			else {
				cache[row][col][pipe_dir] += cache[row + 1][col][1];
			}

			if((home[row + 1][col + 1] == 0) && (home[row][col + 1] == 0)) {
				//move diagonally available
				if(cache[row + 1][col + 1][2] == -1) {
					find_paths(2, row + 1, col + 1);	
					cache[row][col][pipe_dir] += cache[row + 1][col + 1][2];
				}	
				else {
					cache[row][col][pipe_dir] += cache[row + 1][col + 1][2];
				}
			}
		}

		if(pipe_dir == 2) {
			if(home[row][col + 1] == 0) {
				//move horizontally available
				if(cache[row][col + 1][0] == -1) {
					find_paths(0, row, col + 1);	
					cache[row][col][pipe_dir] += cache[row][col + 1][0];
				}	
				else {
					cache[row][col][pipe_dir] += cache[row][col + 1][0];
				}
			}

			if(home[row + 1][col] == 0) {
				//move vertically available
				if(cache[row + 1][col][1] == -1) {
					find_paths(1, row + 1, col);	
					cache[row][col][pipe_dir] += cache[row + 1][col][1];
				}	
				else {
					cache[row][col][pipe_dir] += cache[row + 1][col][1];
				}
			}

			if((home[row][col + 1] == 0) && (home[row + 1][col] == 0) && (home[row + 1][col + 1] == 0)) {
				//move diagonally available
				if(cache[row + 1][col + 1][2] == -1) {
					find_paths(2, row + 1, col + 1);	
					cache[row][col][pipe_dir] += cache[row + 1][col + 1][2];
				}	
				else {
					cache[row][col][pipe_dir] += cache[row + 1][col + 1][2];
				}
			}
		}
	}

	return 0;
}

int main()
{
	scanf("%d", &N);	

	for(int i = 0; i < N; i++) {
		for(int j = 0; j < N; j++) {
			scanf("%d", &home[i][j]);

			cache[i][j][0] = -1;
			cache[i][j][1] = -1;
			cache[i][j][2] = -1;
		}

		home[i][N] = 1;
		cache[i][N][0] = 0;
		cache[i][N][1] = 0;
		cache[i][N][2] = 0;
	}

	for(int j = 0; j <= N; j++) {
		home[N][j] = 1;
		cache[N][j][0] = 0;
		cache[N][j][1] = 0;
		cache[N][j][2] = 0;
	}

	cache[N - 1][N - 1][0] = 1;
	cache[N - 1][N - 1][1] = 1;
	cache[N - 1][N - 1][2] = 1;
	cache[0][1][0] = 0;

	find_paths(0, 0, 1);	

#ifdef DEBUG
	/*
	printf("###cache###\n");
	for(int i = 0; i < N; i++) {
		for(int j = 0; j < N; j++) {
			printf("%d ", cache[i][j]);
		}
		printf("\n");
	}
	
	printf("\n");
	*/
#endif

	printf("%d\n", cache[0][1][0]);

	return 0;
}

