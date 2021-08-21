/*
 * O(N) Solution
 * "Mountain Mania"
 * Gyojun Youn
 */
#include <bits/stdc++.h>
#define eb emplace_back
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
	for(int v : G[i]) if(!cnt[v]) {
		dfs(v);
		cnt[i] += cnt[v];
	}
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);

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
