#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <utility>
#include <iostream>
#include <algorithm>

using namespace std;

int N, K;
int arr[200005];
pair<int, int> station[200005];

int find_search(int target, int first_q) {
	//binary search
	int low = 0;
	int high = N - 1;
	int mid;
#ifdef DEBUG
	printf("### search with %d\n", target);
#endif

	while(low < high) {
		mid = (low + high) / 2;

		if(station[mid].first > target) high = mid - 1;
		else if(station[mid].first < target) {
			low = mid + 1;
		}
		else {
			low = mid;
			break;
		}
	}

	if(station[high].first == target) low = high;

	if((station[low].first != target) && (station[high].first != target)) return -1;

	if(first_q == 1) {
		//if first query
		while((low >= 0) && (station[low].first == target)) {
			low--;
		}
		low++;
	}
	else {
		//if second query
		while((low < N) && (station[low].first == target)) {
			low++;
		}
		low--;
	}

	return station[low].second;
}

int main()
{
	int T;
	scanf("%d", &T);

	for(int i = 0; i < T; i++) {

		scanf("%d %d", &N, &K);

		for(int j = 0; j < N; j++) {
			scanf("%d", &arr[j]);

			station[j].first = arr[j];
			station[j].second = j;
		}

		sort(station, station+N);
#ifdef DEBUG
		printf("### sorted stations ###\n");

		for(int j = 0; j < N; j++) {
			printf("%d %d\n", station[j].first, station[j].second);
		}
		printf("### \n");
#endif
		

		for(int j = 0; j < K; j++) {
			int q_a, q_b;

			scanf("%d %d", &q_a, &q_b);
			
			int a_pos, b_pos;

			a_pos = find_search(q_a, 1);
			b_pos = find_search(q_b, 0);

			if((a_pos == -1) || (b_pos == -1)) printf("NO\n");	
			else if(a_pos <= b_pos) printf("YES\n");
			else printf("NO\n");
		}
	}

	return 0;
}
