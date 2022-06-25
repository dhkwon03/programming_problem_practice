#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <math.h>
#include <algorithm>

using namespace std;

int T, N;
int side[100005];

int main()
{
	scanf("%d", &T);

	for(int i = 0; i < T; i++) {
		scanf("%d", &N);

		for(int j = 0; j < N; j++) {
			scanf("%d", &side[j]);
		}

		sort(side, side+N);	

		int cnt = 1;				

		for(int j = 0; j < N; j++) {
			if(cnt <= side[j]) {
				cnt++;
			}
		}

		printf("Case #%d: %d\n", (i + 1), (cnt - 1));
	}

	return 0;
}
