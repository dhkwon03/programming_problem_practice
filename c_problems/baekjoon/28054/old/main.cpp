#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include <math.h>

using namespace std;

int N;
int K;

int visited_edge[1005][1005];
int visited_vertex[1005];
int visited_vertex_num;
int flag;
int cnt_visited_remain_edge;

/*
K = ceil((n*(n-1)/2) / (n-1)) = ceil(n/2)
*/


int find_path(int cur)
{
	visited_vertex[cur] = 1;
	visited_vertex_num++;

#ifdef DEBUG
	printf("cur : %d\n", cur);
	printf("visited vertex\n");
	for(int i = 1; i <= N; i++) {
		printf("v(%d) : %d\n", i, visited_vertex[i]);
	}
	printf("visited_edge\n");
	for(int i = 1; i <= N; i++) {
		for(int j = 1; j <= N; j++) {
			printf("v1(%d), v2(%d) : %d\n", i, j, visited_edge[i][j]);
		}
	}
	printf("\n");
#endif
	
	if(visited_vertex_num == N) {
		flag = 1;

		return 0; 
	}

	for(int i = 1; i <= N; i++) {
		if((visited_vertex[i] == 0) && (visited_edge[cur][i] == 0)) {
			visited_edge[cur][i] = 1;
			visited_edge[i][cur] = 1;
			find_path(i);

			if(flag == 1) {
				printf("%d %d\n", i, cur);		
				break;
			}
			else {
				visited_edge[cur][i] = 0;
				visited_edge[i][cur] = 0;
			}
		}
	}

	if(flag == 0) {
		visited_vertex[cur] = 0;
		visited_vertex_num--;
	}

	return 0;
}

int find_last_path(int cur)
{
	visited_vertex[cur] = 1;
	visited_vertex_num++;
	
	if(visited_vertex_num == N) {
		flag = 1;

		return 0; 
	}

	for(int i = 1; i <= N; i++) {
		if(cnt_visited_remain_edge == ((((N / 2) + 1) * (N - 1)) - (N * (N - 1) / 2))) {
			if(visited_vertex[i] == 0) {
				find_last_path(i);

				if(flag == 1) {
					printf("%d %d\n", i, cur);
					break;
				}
			}
		}
		else {
			if((visited_vertex[i] == 0) && (visited_edge[cur][i] == 0)) {
				cnt_visited_remain_edge++;
				visited_edge[cur][i] = 1;
				visited_edge[i][cur] = 1;
				find_last_path(i);

				if(flag == 1) {
					printf("%d %d\n", cur, i);
					break;
				}
				else {
					cnt_visited_remain_edge--;
					visited_edge[cur][i] = 0;
					visited_edge[i][cur] = 0;
				}
			}
		}
	}

	if(flag == 0) {
		visited_vertex[cur] = 0;
		visited_vertex_num--;
	}

	return 0;
}

int main()
{
	cin >> N;	
	
	if(N % 2 == 0) K = N / 2;
	else K = (N / 2) + 1;

	cout << K << "\n";	

	//initialization
	for(int i = 1; i <= N; i++) {
		for(int j = 1; j <= N; j++) {
			if(i != j) {
				visited_edge[i][j] = 0;
			}
			else {
				visited_edge[i][j] = 1;
			}
		}
	}

	if(N % 2 == 0) {
		for(int i = 1; i <= (N / 2); i++) {
			for(int j = 1; j <= N; j++) {
				visited_vertex[j] = 0;
			}
			visited_vertex_num = 0;
			flag = 0;

			for(int j = 1; j <= N; j++) {
				find_path(j);

				if(flag == 1) break;
			}
		}
	}
	else {
		for(int i = 1; i <= (N / 2); i++) {
			for(int j = 1; j <= N; j++) {
				visited_vertex[j] = 0;
			}

			visited_vertex_num = 0;
			flag = 0;

			for(int j = 1; j <= N; j++) {
				find_path(j);

				if(flag == 1) break;
			}
		}

		for(int i = 1; i <= N; i++) {
			for(int j = 1; j <= N; j++) {
				if(visited_edge[i][j] == 0) {
#ifdef DEBUG
					printf("####### I'm in!!!\n");
#endif
					for(int k = 1; k <= N; k++) {
						visited_vertex[k] = 0;
					}

					visited_vertex_num = 0;
					flag = 0;
					cnt_visited_remain_edge = 0;

					find_last_path(i);

					if(flag == 1) break;
				}
			}
		}
	}

	return 0;
}
