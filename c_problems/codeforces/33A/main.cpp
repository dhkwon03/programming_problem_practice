#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int main()
{
	int n, m, k;
	int row_num[1005];
	int r, c;

	cin >> n >> m >> k;

	for(int i = 0; i < m; i++) {
		row_num[i] = 9999999;
	}

	for(int i = 0; i < n; i++) {
		cin >> r >> c;

		if(row_num[r - 1] > c) row_num[r - 1] = c;
	}

	int cnt;
	cnt = 0;
	for(int i = 0; i < m; i++) {
		cnt += row_num[i];	
	}

	cout << ((cnt > k) ? k : cnt) << "\n";


	return 0;
}
