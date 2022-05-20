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
int T, N;

int solve(int idx)
{
	if(chain[idx].in.size() == 0) {
		chain[idx].maxv = chain[idx].num;
		//chain[idx].sum = chain[idx].num;	

		return 0;
	}

	int max_min = 1100000000;
	int maxmin_idx;
	for(int i = 0; i < chain[idx].in.size(); i++) {
		solve(chain[idx].in[i]);	

		if(max_min > chain[chain[idx].in[i]].maxv) {
			max_min = chain[chain[idx].in[i]].maxv;
			maxmin_idx = chain[idx].in[i];
		}
	}

	chain[idx].maxv = max(chain[idx].num, chain[maxmin_idx].maxv);

	for(int i = 0; i < chain[idx].in.size(); i++) {
		if(chain[idx].in[i] != maxmin_idx) {
			chain[idx].sum += chain[chain[idx].in[i]].maxv + chain[chain[idx].in[i]].sum; 
		}
	}	

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
		}	
		for(int j = 0; j < N; j++) {
			int input_to;

			scanf("%d", &input_to);

			chain[j+1].out = input_to;	
			chain[input_to].in.push_back(j + 1);
		}

		long long int ans = 0;

		for(int j = 1; j <= N; j++) {
			if(chain[j].out == 0) {
				solve(j);
				chain[j].sum += chain[j].maxv;
				ans += chain[j].sum;
			}	
		}

		printf("Case #%d: %lld\n", (i + 1), ans);

	}

	return 0;
}
