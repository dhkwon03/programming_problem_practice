#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>

using namespace std;

int main()
{
	int t;
	int x, y;


	scanf("%d", &t);

	for(int i = 0; i < t; i++) {
		scanf("%d %d", &x, &y);

		long long int dis;
		dis = y - x;

		long long int cnt;
		cnt = 1;
		long long int ans;
		while(1) {
			if((dis <= (cnt * (cnt + 1) - cnt)) && (dis > (cnt * (cnt + 1) - 2 * cnt))) {
				ans = 2 * cnt - 1;		
				break;
			}
			else if((dis > (cnt * (cnt + 1) - cnt)) && (dis <= cnt * (cnt + 1))) {
				ans = 2 * cnt;	
				break;
			}

			cnt++;
		}

		printf("%lld\n", ans);
	}

	return 0;
}
