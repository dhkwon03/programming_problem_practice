#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <math.h>

using namespace std;

int T;
int min_c, min_m, min_y, min_k;

int main()
{
	scanf("%d", &T);

	for(int i = 0; i < T; i++) {
		min_c = min_m = min_y = min_k = 10000000;
		for(int j = 0; j < 3; j++) {
			int C, M, Y, K;
			scanf("%d %d %d %d", &C, &M, &Y, &K);

			min_c = min(min_c, C);
			min_m = min(min_m, M);
			min_y = min(min_y, Y);
			min_k = min(min_k, K);
		}		

		if((min_c + min_m + min_y + min_k) < 1000000) printf("Case #%d: IMPOSSIBLE\n", (i + 1)); 
		else {
			int sum = 1000000;	
			
			printf("Case #%d:", (i + 1));
			if(min_c >= sum) {
				printf(" %d", sum); 
				sum = 0;
			}
			else {
				printf(" %d", min_c); 
				sum -= min_c;
			}

			if(min_m >= sum) {
				printf(" %d", sum); 
				sum = 0;
			}
			else {
				printf(" %d", min_m); 
				sum -= min_m;
			}

			if(min_y >= sum) {
				printf(" %d", sum); 
				sum = 0;
			}
			else {
				printf(" %d", min_y); 
				sum -= min_y;
			}

			if(min_k >= sum) {
				printf(" %d", sum); 
				sum = 0;
			}
			else {
				printf(" %d", min_k); 
				sum -= min_k;
			}

			printf("\n");
		}
	}		

	return 0;
}
