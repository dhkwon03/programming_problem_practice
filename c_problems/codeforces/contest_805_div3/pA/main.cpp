#include <stdio.h>
#include <stdlib.h>
#include <math.h>

using namespace std;

int t;
int m;

int main()
{
	scanf("%d", &t);

	for(int i = 0; i < t; i++) {
		scanf("%d", &m);

		int power_num;
		for(power_num = 0; power_num <= 9; power_num++) {
			int cmp_num = m - pow(10, power_num);

			if(cmp_num < 0) break;
		}

		power_num--;

		printf("%d\n", m - int(pow(10, power_num)));
	}

	return 0;
}
