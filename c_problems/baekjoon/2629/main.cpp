#include <stdio.h>
#include <iostream>
#include <math.h>
#include <algorithm>

using namespace std;

int N, M;
int weight[35];
int weight_sum;
int cache[35][40005];
int visited[35][40005];

int recursive_check(int cur_idx, int cur_weight)
{
	if(cur_weight > weight_sum) return 0;

	visited[cur_idx][cur_weight] = 1;

	if(cache[cur_idx][cur_weight] == 1) return 1;
	else if(cur_idx == 0) return 0;	

	int result;
	if(visited[cur_idx - 1][abs(cur_weight - weight[cur_idx])] == 0) {
		result = recursive_check((cur_idx - 1), abs(cur_weight - weight[cur_idx]));		
		
		if(result == 1) {
			cache[cur_idx][cur_weight] = 1;
			return 1;
		}
	}

	if(visited[cur_idx - 1][abs(cur_weight + weight[cur_idx])] == 0) {
		result = recursive_check((cur_idx - 1), abs(cur_weight + weight[cur_idx]));		
		
		if(result == 1) {
			cache[cur_idx][cur_weight] = 1;
			return 1;
		}
	}

	if(visited[cur_idx - 1][cur_weight] == 0) {
		result = recursive_check((cur_idx - 1), (cur_weight));		
		
		if(result == 1) {
			cache[cur_idx][cur_weight] = 1;
			return 1;
		}
	}

	return 0;
}

bool compare(int a, int b)
{
	return (a > b);
}

int main()
{
	cin >> N;

	weight_sum = 0;
	for(int i = 0; i < N; i++) {
		cin >> weight[i];
		weight_sum += weight[i];
	}		

	sort(weight, weight + N, compare);
		
	cin >> M;

	for(int j = 0; j < N; j++) {
		for(int k = 0; k <= weight_sum; k++) {
			cache[j][k] = 0;		
		}	
	}

	for(int i = 0; i < N; i++) {
		cache[i][weight[i]] = 1;
		cache[i][0] = 1;
	}

	for(int i = 0; i < M; i++) {
		int check_weight;	

		for(int j = 0; j < N; j++) {
			for(int k = 0; k <= weight_sum; k++) {
				visited[j][k] = 0;		
			}	
		}

		cin >> check_weight;	
		if(check_weight > weight_sum) cout << "N ";
		else {
			recursive_check((N - 1), check_weight);						

			if(cache[N - 1][check_weight] == 1) cout << "Y ";
			else cout << "N ";
		}
	}
	cout << endl;

	return 0;
}
