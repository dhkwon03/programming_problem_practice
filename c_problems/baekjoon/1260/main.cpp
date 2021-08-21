#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <queue>

using namespace std;

int n, m, v;
vector<int> graph[1005];
int visited[1005] = {0,};
int visited2[1005] = {0,};
queue<int> to_visit;

bool compare(int a, int b)
{
	return (a < b);
}

int dfs_print(int cur_v) {
	visited[cur_v] = 1;
	cout << cur_v << " ";	

	for(int i = 0; i < graph[cur_v].size(); i++) {
		if(visited[graph[cur_v][i]] == 0) {
			dfs_print(graph[cur_v][i]);
		}
	}

	return 0;
}

int bfs_print(int st_v) {
	visited2[st_v] = 1;	
	to_visit.push(st_v);

	while(!to_visit.empty()) {
		int cur_v;

		cur_v = to_visit.front();
		cout << cur_v << " ";	
		to_visit.pop();

		for(int i = 0; i < graph[cur_v].size(); i++) {
			if(visited2[graph[cur_v][i]] == 0) {
				to_visit.push(graph[cur_v][i]);
				visited2[graph[cur_v][i]] = 1;
			}
		}
			
	}

	return 0;
}

int main()
{
	cin >> n >> m >> v;

	for(int i = 0; i < m; i++) {
		int input_st, input_en;		

		cin >> input_st >> input_en;

		graph[input_st].push_back(input_en);		
		graph[input_en].push_back(input_st);	
	}	

	for(int i = 1; i <= n; i++) {
		sort(graph[i].begin(), graph[i].end(), compare);
	}		

	dfs_print(v);
	cout << "\n";	
	bfs_print(v);	
	cout << endl;
	
	return 0;
}
