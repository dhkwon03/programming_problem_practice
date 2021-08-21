#include <stdio.h>
#include <stdlib.h>
#include <math.h>

using namespace std;

int main()
{
	int n;

	scanf("%d", &n);

	int cur;

	cur = n % 5;
	while(cur <= n) {
		if((cur % 3) == 0) {
			break;
		}

		cur += 5;
	}

	if(cur > n) {
		printf("-1\n");
	}
	else {
		printf("%d\n", (cur / 3) + ((n - cur) / 5));
	}

	return 0;
}
