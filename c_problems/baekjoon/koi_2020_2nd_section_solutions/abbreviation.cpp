#include <bits/stdc++.h>
#include "testlib.h"
#include "const.h"
using namespace std;

// '약자' Model solution
// Time complexity: O(|S| + |\Omega| |T|)

string S, T;
// nxt[i][c] := T[i] 이후에 있는, 첫번째 문자 c의 위치
int nxt[maxM][maxC];

int main() {
	cin >> S >> T;

	for (int c=0; c<maxC; c++) {
		vector<int> pos;
		for (int i=0; i<T.size(); i++) if (T[i] == 'a' + c) pos.push_back(i);
		
		if (pos.empty()) {
			for (int i=0; i<T.size(); i++) nxt[i][c] = -1;
		} else {
			pos.push_back(pos[0] + T.size());
			int j=0;
			for (int i=0; i<T.size(); i++) {
				while (pos[j] <= i) j++;
				nxt[i][c] = pos[j];
			}
		}
	}

	int ans=0, j=T.size()-1;
	for (int i=0; i<S.size(); i++) {
		j = nxt[j][S[i]-'a'];
		if (j == -1) {
			cout << -1 << '\n';
			return 0;
		}
		if (j >= T.size()) {
			j -= T.size();
			ans++;
		}
	}

	cout << ans << '\n';
}