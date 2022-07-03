#include <stdio.h>
#include <cassert>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <algorithm>

using namespace std;

int arr[105][105];
int fixed_cnt[105][105];
int minop[105][105];
int T;
int E, W;

int find_fixed_cnt(int stepa, int stepb) {
	if(fixed_cnt[stepa][stepb] != -1) return fixed_cnt[stepa][stepb];	
	else {	
		int minarr[105];

		for(int i = stepa; i <= stepb; i++) {
			for(int j = 0; j < W; j++) {
				if(i == stepa) minarr[j] = arr[i][j];		
				else minarr[j] = min(minarr[j], arr[i][j]);
			}
		}

		int res = 0;
		for(int i = 0; i < W; i++) {
			res += minarr[i];	
		}

		fixed_cnt[stepa][stepb] = res;

#ifdef DEBUG
		if(fixed_cnt[stepa][stepb] < 0) {
			printf("#error : fixed_cnt = %d, stepa = %d, stepb = %d\n", fixed_cnt[stepa][stepb], stepa, stepb);
		}
		//assert(fixed_cnt[stepa][stepb] >= 0);
#endif

		return res;
	}
}

int find_op_cnt(int stepa, int stepb) {
#ifdef DEBUG
	//assert((stepa >= 0) && (stepb >= 0));
	if((stepa < 0) || (stepb < 0)) {
		printf("#error : stepa = %d, stepb = %d\n", stepa, stepb);
	}
#endif
	if(stepa == stepb) {
		minop[stepa][stepb] = 0;
		return 0;
	}

	if(minop[stepa][stepb] != -1) return minop[stepa][stepb];

	for(int i = stepa; i < stepb; i++) {
		if(i == stepa) {
			minop[stepa][stepb] = 2 * (find_fixed_cnt(stepa, i) + find_fixed_cnt(i + 1, stepb) - 2 * find_fixed_cnt(stepa, stepb)) 
				+ find_op_cnt(stepa, i) + find_op_cnt(i + 1, stepb);
		}
		else {
			minop[stepa][stepb] = min(minop[stepa][stepb], 
					2 * (find_fixed_cnt(stepa, i) + find_fixed_cnt(i + 1, stepb) - 2 * find_fixed_cnt(stepa, stepb)) 
					+ find_op_cnt(stepa, i) + find_op_cnt(i + 1, stepb));
		}
	}

	return minop[stepa][stepb];
}

int main()
{
	scanf("%d", &T);

	for(int i = 0; i < T; i++) {
		scanf("%d %d", &E, &W);

		for(int j = 0; j < E; j++) {
			for(int k = 0; k < E; k++) {
				fixed_cnt[j][k] = -1;
				minop[j][k] = -1;
			}

			for(int k = 0; k < W; k++) {
				scanf("%d", &arr[j][k]);	
			}
		}

		find_op_cnt(0, (E-1));		

		printf("Case #%d: %d\n", (i + 1), (minop[0][E-1] + 2 * find_fixed_cnt(0, E-1)));
	}

	return 0;
}
