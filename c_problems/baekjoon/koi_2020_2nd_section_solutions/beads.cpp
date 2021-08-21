// correct

#include <bits/stdc++.h>

using namespace std;

int D[2020];
int n, k, q, f, s;

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);

	int i, j, x;

	cin >> n >> k >> q;

	for(i = 1; i <= n; i ++){
		for(j = 0; j < k; j ++){
			cin >> x; D[x] --; D[i] ++;
			if(x < i) s ++;
			if(x != 1 && i == 1) f = 1;
		}
	}

	if(!f) s ++;
	for(i = 1; i <= n; i ++){
		if(D[i]) s = 2e9;
	}

	cout << (s <= q) << "\n";

	return 0;
}