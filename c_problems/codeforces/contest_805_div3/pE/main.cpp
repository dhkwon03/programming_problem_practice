#include <stdio.h>
#include <utility>
#include <vector>
#include <math.h>
#include <algorithm>
#include <stdlib.h>
#include <string.h>

using namespace std;

int T;
int N;

int main()
{
	scanf("%d", &T);

	for(int i = 0; i < T; i++) {
		pair<int, int> arr[200005];
		int cnt[200005];
		scanf("%d", &N); 

		for(int j = 0; j < N; j++) {
			scanf("%d %d", &arr[j].first, &arr[j].second);

			if(arr[j].first > arr[j].second) {
				int temp = arr[j].first;
				arr[j].first = arr[j].second;
				arr[j].second = temp;
			}
			cnt[j] = 0;
		}

		sort(arr, arr+N);

		int flag = 0;
		for(int j = 0; j < N; j += 2) {
			if(arr[j] != arr[j+1]) {
				
			}
		}
		
		if(flag == 1) printf("NO\n");
		else printf("YES\n");
	}

	return 0;
}
