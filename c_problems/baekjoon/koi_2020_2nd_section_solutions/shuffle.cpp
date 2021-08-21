/*
 * Official O(N) Solution
 * "Sequence Shuffle"
 * Gyojun Youn
 */
#include <bits/stdc++.h>
using namespace std;

vector<int> A;

int N, K;

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);

	cin >> N;

	A.resize(N);
	for(int i = 0; i < N; i++)
		cin >> A[i];
	
{
	bool flag = true;
	for(int i = 1; i < N; i++)
		flag &= A[i-1] <= A[i];
	if(flag) {
		puts("0");
		exit(0);
	}
}

	// Gyojun's Algorithm
	for(int i = 0; i < N;) {
		K++;
		for(; i+1 < N && A[i] <= A[i+1]; i++);
		for(i++; i+1 < N && A[i] >= A[i+1]; i++);
		i++;
	}

	K--;
	cout << (K ? 33 - __builtin_clz(K) : 1) << endl;
	return 0;
}
