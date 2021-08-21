/*
 * O(N) Solution
 * "Mountain Mania"
 * Gyojun Youn
 */
#include <stdio.h>
#include <vector>
#include <stdlib.h>
#include <iostream>
#define eb push_back
using namespace std;
typedef long long ll;

const int MAXN = 300055;

vector<int> G[MAXN];

int cnt[MAXN];

ll Ans;
int N;

ll f(ll n) { return n * (n-1) / 2; }

void dfs(int i) {
	cnt[i] = 1;
	for(vector<int>::iterator v = G[i].begin(); v < G[i].end(); v++)  {
		if(!cnt[*v]) {
		dfs(*v);
		cnt[i] += cnt[*v];
		}
	}
}

int main() {
	cin >> N;
	for(int i = 1, a, b; i < N; i++) {
		cin >> a >> b;
		G[a].eb(b);
		G[b].eb(a);
	}

	// Gyojun's DFS
	dfs(1);

	// Based on the edge (i - par[i])
	for(int i = 2; i <= N; i++)
		Ans += f(N) - f(N - cnt[i]);
	
	cout << Ans << endl;
	return 0;
}

