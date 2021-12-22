#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include <utility>
#include <math.h>

using namespace std;

int N;
int arr[100005];
pair<int, int> ans;
int min_diff;

int binary_search(int target)
{
	int left, right;

	left = 0;
	right = N - 1;

	while(1) {
		if(abs(left - right) <= 1) {
			break;
		}

		int mid = (left + right) / 2;

		if(arr[mid] <= target) left = mid;
		else right = mid;	
	}

	if(arr[left] == (-1) * (target)) return right;
	else if(arr[right] == (-1) * (target)) return left;
	else {
		if(abs(arr[left] - target) <= abs(arr[right] - target)) return left;
		else return right;
	}
}

int main()
{
	cin >> N;

	for(int i = 0; i < N; i++) {
		cin >> arr[i];
	}	

	sort(arr, arr+N);

	min_diff = 2000000000;

	for(int i = 0; i < N; i++) {
		int idx;

		idx = binary_search((-1) * arr[i]);
		if(min_diff > abs(arr[i] + arr[idx])) {
			ans.first = arr[i];
			ans.second = arr[idx];	
			min_diff = abs(arr[i] + arr[idx]);
		}
	}	

	if(ans.first < ans.second) {
		cout << ans.first << " " << ans.second << endl;
	}
	else {
		cout << ans.second << " " << ans.first << endl;
	}

	return 0;
}
