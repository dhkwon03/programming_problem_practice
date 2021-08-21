#include <stdio.h>
#include <stdlib.h>
#include <math.h>

using namespace std;

int main()
{
	int t;
	int h, w, n;

	scanf("%d", &t);

	for(int i = 0; i < t; i++) {
		scanf("%d %d %d", &h, &w, &n);

		int floor, room_idx;

		floor = ((n % h) == 0) ? h : (n % h);

		room_idx = ((n % h) == 0) ? (n / h) : ((n / h) + 1);

		if(room_idx < 10) {
			printf("%d0%d\n", floor, room_idx);
		}
		else {
			printf("%d%d\n", floor, room_idx);
		}
	}

	return 0;
}
