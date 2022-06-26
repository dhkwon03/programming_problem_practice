#include <stdio.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include <stdlib.h>
#include <math.h>

using namespace std;

typedef struct {
	int num;
	int parent;
	vector<int> child;
	//maximum number until that node through the path
	int maxn;
	//'fun' of that subtree which has this node as the root node
	long long int fun;
}TREE;

int T, N;
vector<TREE> arr;

int dfs(int cur) 
{
	if(arr[cur].child.empty()) {
		arr[cur].maxn = arr[cur].num;		
		return 0;
	}

	for(int i = 0; i < arr[cur].child.size(); i++) {
		dfs(arr[cur].child[i]);
	}

	if(arr[cur].child.size() >= 2) {
		int min_maxn = 2000000000;
		int min_maxn_child;
		long long int fun_sum = 0;
		for(int i = 0; i < arr[cur].child.size(); i++) {
			if(min_maxn > arr[arr[cur].child[i]].maxn) {
				min_maxn = arr[arr[cur].child[i]].maxn;
				min_maxn_child = arr[cur].child[i];
			}

			fun_sum += (arr[arr[cur].child[i]].fun + arr[arr[cur].child[i]].maxn); 
		}

		fun_sum -= arr[min_maxn_child].maxn;	

		arr[cur].maxn = max(arr[min_maxn_child].maxn, arr[cur].num);
		arr[cur].fun = fun_sum;
	}
	else {
		arr[cur].maxn = max(arr[arr[cur].child[0]].maxn, arr[cur].num);
		arr[cur].fun = arr[arr[cur].child[0]].fun;
	}

	return 0;	
}

int main()
{
	scanf("%d", &T);

	for(int i = 0; i < T; i++) {
		arr.clear();

		scanf("%d", &N);		
	
		for(int j = 0; j < N; j++) {
			TREE input;

			input.maxn = 0;
			input.fun = 0;

			scanf("%d", &input.num); 

			arr.push_back(input);	
		}

		for(int j = 0; j < N; j++) {
			scanf("%d", &arr[j].parent);

			if(arr[j].parent != 0) {
				arr[arr[j].parent - 1].child.push_back(j);
			}
		}

		long long int ans = 0;

		for(int j = 0; j < N; j++) {
			if(arr[j].parent == 0) {
				dfs(j);		
				arr[j].fun += arr[j].maxn;
				ans += arr[j].fun;
			}
		}


		printf("Case #%d: %lld\n", (i + 1), ans);
	}

	return 0;
}
