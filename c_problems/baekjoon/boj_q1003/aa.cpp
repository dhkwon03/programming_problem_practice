#include <stdio.h>
#include <stdlib.h>

using namespace std;

typedef struct __ARR {
	int zero, one;
}ARR;

int t, n;
ARR arr[50];

int main()
{
	scanf("%d", &t);
		
	ARR init;
	
	init.zero = 1;
	init.one = 0;

	arr[0] = init;

	init.zero = 0;
	init.one = 1;

	arr[1] = init;

	for(int i = 2; i <= 40; i++) {
		ARR temp;

		temp.zero = arr[i-1].zero + arr[i-2].zero;
		temp.one = arr[i-1].one + arr[i-2].one;	

		arr[i] = temp;
	}

	for(int i = 0; i < t; i++) {
		scanf("%d", &n);

		printf("%d %d\n", arr[n].zero, arr[n].one);
	}

	return 0;
}

