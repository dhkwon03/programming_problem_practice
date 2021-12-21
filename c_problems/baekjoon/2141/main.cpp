#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <algorithm>

using namespace std;

typedef struct __TOWN {
	long long int x, a;
}TOWN;

int N;
TOWN arr[100005];
int min_pos;
long long int a_sum;

bool compare (TOWN p, TOWN q) { return (p.x < q.x); }

int main()
{
	cin >> N;

	a_sum = 0;
	for(int i = 0; i < N; i++) {
		cin >> arr[i].x >> arr[i].a;

		a_sum += arr[i].a;
	}
	
	sort(arr, arr+N, compare);	

	long long int a_cur_left = 0;

	for(int i = 0; i < N; i++) {
		a_cur_left += arr[i].a;

		if(a_cur_left >= ((a_sum + 1) / 2)) {
			min_pos = arr[i].x;
			break;
		}
	}

	cout << min_pos << endl;
	
	return 0;
}
