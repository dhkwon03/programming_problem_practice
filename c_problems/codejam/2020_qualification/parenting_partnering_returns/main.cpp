#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <algorithm>

using namespace std;

typedef struct __TIME {
	int st, end;
	//index before sorting
	int idx;
}TIME;

int t;
int n;
TIME arr[1005];
//ans[i] == 0 : none, 1 : C, 2 : J
int ans[1005];
//c_last_time, j_last_time
int clt, jlt;

bool compare(TIME a, TIME b) {
	if(a.st == b.st) return (a.end < b.end);
	else return (a.st < b.st);
}

int main()
{
	cin >> t;

	for(int i = 0; i < t; i++) {
		cin >> n;

		for(int j = 0; j < n; j++) {
			cin >> arr[j].st >> arr[j].end;
			arr[j].idx = j;
		}

		sort(arr, arr + n, compare);

		fill(ans, ans + n, 0);			
		clt = 0;
		jlt = 0;
		int flag = 0;

		for(int j = 0; j < n; j++) {
			if(clt <= arr[j].st) {
				ans[arr[j].idx] = 1;
				clt = arr[j].end;
			}
			else if(jlt <= arr[j].st) {
				ans[arr[j].idx] = 2;
				jlt = arr[j].end;
			}
			else {
				flag = 1;
				break;
			}
		}

		if(flag == 1) cout << "Case #" << (i + 1) << ": " << "IMPOSSIBLE\n";
		else {
			cout << "Case #" << (i + 1) << ": ";
			for(int j = 0; j < n; j++) {
				if(ans[j] == 1) cout << "C";
				else if(ans[j] == 2) cout << "J";
			}
			cout << "\n";
		}
	}


	return 0;
}
