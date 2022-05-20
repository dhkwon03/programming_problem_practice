#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <stdlib.h>

using namespace std;

typedef struct {
	//out to abyss : 0
	vector<int> in;
	int out;
	//node number
	int num;
	//max value
	int maxv;
	//sum of answers
	long long int sum;
}GRAPH;

GRAPH chain[100005];
int visited[100005];
int used[100005];
int T, N;
long long int ans = 0;
long long int cur_res = 0;
vector<int> trigger;
vector<int> trigger_order;

int solve()
{
	cur_res = 0;
	for(int i = 0; i < trigger_order.size(); i++) {
		int now_max = 0;
		int cur_node = trigger_order[i];
		while(1) {
			visited[cur_node] = 1;
			now_max = max(now_max, chain[cur_node].num);		

			if((chain[cur_node].out == 0) || (visited[chain[cur_node].out] == 1)) break;

			cur_node = chain[cur_node].out;
		}
		cur_res += now_max;
	}

	return 0;
}

int permutation(int cur_trig, int cur_cnt)
{
	trigger_order.push_back(cur_trig);
	used[cur_trig] = 1;

	if(cur_cnt == trigger.size()) {
		for(int i = 1; i <= N; i++) visited[i] = 0;
		solve();

		ans = max(ans, cur_res);
		used[cur_trig] = 0;
		trigger_order.pop_back();

		return 0;
	}	

	for(int i = 0; i < trigger.size(); i++) {
		if(used[trigger[i]] == 0) {
			permutation(trigger[i], cur_cnt + 1);
		}
	}

	used[cur_trig] = 0;
	trigger_order.pop_back();

	return 0;
}


int main()
{
	scanf("%d", &T);

	for(int i = 0; i < T; i++) {
		scanf("%d", &N);

		for(int j = 0; j < N; j++) {
			scanf("%d", &chain[j+1].num);

			chain[j+1].maxv = 0;
			chain[j+1].sum = 0;
			chain[j+1].in.clear();
			visited[j+1] = 0;
			used[j+1] = 0;
		}	
		for(int j = 0; j < N; j++) {
			int input_to;

			scanf("%d", &input_to);

			chain[j+1].out = input_to;	
			chain[input_to].in.push_back(j + 1);
		}


		trigger.clear();
		/*
		for(int j = 1; j <= N; j++) {
			if(chain[j].out == 0) {
				solve(j);
				chain[j].sum += chain[j].maxv;
				ans += chain[j].sum;
			}	
		}
		*/

		for(int j = 1; j <= N; j++) {
			if(chain[j].in.size() == 0) {
				trigger.push_back(j);
			}
		}

		for(int j = 0; j < trigger.size(); j++) {
			trigger_order.clear();
			permutation(trigger[j], 1);
		}

		printf("Case #%d: %lld\n", (i + 1), ans);
		ans = 0;

	}

	return 0;
}
