#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include <stack>

//union-find algorithm + path compression

using namespace std;

struct CHECK {
	int st, end;

	CHECK(int first, int second) : st(first), end(second) {};
};

int N, Q;
int root[200005];
int parent_input[200005];
//ans, discon, query --> ordered in opposite way
stack<int> ans;
//disconnection = discon
stack<int> discon;
stack<CHECK> query;
stack<int> order;

int find(int cur) {
	if(root[cur] == cur) {
		return cur;
	}
	else {
		return (root[cur] = find(root[cur]));
	}	
}

int merge(int parent, int child) {
	int root_par;

	root_par = find(parent);

	root[child] = root_par;

	return 0;
}

int main()
{
	scanf("%d %d", &N, &Q);

	parent_input[1] = 0;
	for(int i = 2; i <= N; i++) {
		scanf("%d", &parent_input[i]);
	}		

	for(int i = 0; i < (N + Q - 1); i++) {
		int mode;
		int num1, num2;

		scanf("%d", &mode);		

		order.push(mode);

		if(mode == 0) {
			scanf("%d", &num1);		

			discon.push(num1);
		}
		else if(mode == 1) {
			scanf("%d %d", &num1, &num2);	

			query.push(CHECK(num1, num2));
		}
	}

	//initialize
	for(int i = 1; i <= N; i++) {
		root[i] = i;
	}	

	while(!order.empty()) {
		if(order.top() == 0) {
			merge(parent_input[discon.top()], discon.top());
			discon.pop();
		}
		else if(order.top() == 1) {
			ans.push((find(query.top().st) == find(query.top().end)) ? 1 : 0);
			query.pop();
		}

		order.pop();
	}

	while(!ans.empty()) {
		if(ans.top() == 0) printf("NO\n");
		else if(ans.top() == 1) printf("YES\n");

		ans.pop();
	}

	return 0;
}
