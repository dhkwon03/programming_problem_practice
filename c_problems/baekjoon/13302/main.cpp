#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>

using namespace std;

int N, M;
int days[105];
//cache[a][b] = c --> a'th day, number of coupon : b, min required cost until end : c
//cost should be '* 1000' at the end
int cache[105][105];

int solve(int cur_day, int coupon)
{
	if(cur_day > N) return 0;	
	if(cache[cur_day][coupon] != 100000) return cache[cur_day][coupon];

	if(days[cur_day] == 1) {
		cache[cur_day][coupon] = min(cache[cur_day][coupon], solve(cur_day + 1, coupon)); 
	}

	cache[cur_day][coupon] = min(cache[cur_day][coupon], solve(cur_day + 1, coupon) + 10); 
	cache[cur_day][coupon] = min(cache[cur_day][coupon], solve(cur_day + 3, coupon + 1) + 25); 
	cache[cur_day][coupon] = min(cache[cur_day][coupon], solve(cur_day + 5, coupon + 2) + 37); 

	if(coupon >= 3) {
		cache[cur_day][coupon] = min(cache[cur_day][coupon], solve(cur_day + 1, coupon - 3));
	}

	return cache[cur_day][coupon];
}

int main()
{
	scanf("%d %d", &N, &M);	

	//init
	for(int i = 1; i <= N; i++) {
		days[i] = 0;
		for(int j = 0; j <= 100; j++) {
			cache[i][j] = 100000;		
		}
	}

	for(int i = 0; i < M; i++) {
		int not_going_input;
		scanf("%d", &not_going_input);

		days[not_going_input] = 1;	
	}

	solve(1, 0);

	printf("%d\n", (cache[1][0] * 1000));

	return 0;
}
