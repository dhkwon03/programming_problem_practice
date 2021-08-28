/*
int sum_cnt = 0;
int power_n = 1;
int prime_num[105];
//available numbers for power_n
vector<long long int> avail_num;
//exponent
int expo[105];

int combination(int n, int m) {
	//numerator, denominator
	long long int numer, deno; 
	
	numer = 1;
	deno = 1;
	for(int i = n; i > (n - m); i--) {
		numer = numer * i;	
	}

	for(int i = 1; i <= m; i++) {
		deno = deno * i;
	}

	return (numer / deno);	
}

int generate(int cur_prime, int expo_sum)
{
	if(cur_prime == (K - 1)) {
		expo[cur_prime] = power_n - expo_sum;

		long long int ans = 1;

		for(int i = 0; i < K; i++) {
			ans *= pow(prime_num[i], expo[i]);
		}
		
		avail_num.push_back(ans);

		return 0;
	}

	for(int i = 0; i <= (power_n - expo_sum); i++) {
		expo[cur_prime] = i;

		generate(cur_prime + 1, expo_sum + i);
	}

	return 0;
}	

int main()
{
	scanf("%d %d", &K, &N);	

	for(int i = 0; i < K; i++) {
		scanf("%d", &prime_num[i]);	
	}	

	while(1) {
		sum_cnt += combination((K + power_n - 1), power_n);	

		if(sum_cnt >= N) {
			sum_cnt -= combination((K + power_n - 1), power_n);
			break;
		}
		else power_n++;
	}	

#ifdef DEBUG
	printf("###power_n = %d\n", power_n);
#endif

	generate(0, 0);		

	sort(avail_num.begin(), avail_num.end());

	printf("%lld\n", avail_num[N - sum_cnt - 1]);

	return 0;	
}
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <map>

using namespace std;


int K, N;
long long int prime[105];
priority_queue<long long, vector<long long>, greater<long long> > pq;
long long max_num;
int cnt;
map<long long, bool> same_check;

int main()
{
	scanf("%d %d", &K, &N);	

	max_num = 0;
	for(int i = 0; i < K; i++) {
		scanf("%lld", &prime[i]);

		pq.push(prime[i]);

		max_num = max(max_num, prime[i]);
	}	

	cnt = 1;
	long long top_value;

	while(1) {
		top_value = pq.top();

		pq.pop();

		if(cnt == N) {
			break;		
		}	
		
		cnt++;

		for(int i = 0; i < K; i++) {
			long long new_num;

			new_num = top_value * prime[i];

			if((pq.size() > N) && (max_num < new_num)) continue;

			if(!same_check.count(new_num)) {
				same_check[new_num] = true;	

				max_num = max(max_num, new_num);			

				pq.push(new_num);
			}	
		}
	}

	printf("%lld\n", top_value);


	return 0;
}
