#include <stdio.h>
#include <math.h>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int T;

int n, z;

int main()
{
	scanf("%d", &T);

	for(int i = 0; i < T; i++) {
		scanf("%d %d", &n, &z);

		int ans = -1;
		for(int j = 0; j < n; j++) {
			int input;
			scanf("%d", &input);

			ans = max(ans, (input | z));
		}

		printf("%d\n", ans);
	}

	return 0;
}
