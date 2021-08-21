#include <stdio.h>
#include <stdlib.h>
#include <math.h>

using namespace std;

int main()
{
	int a, b, v;

	scanf("%d %d %d", &a, &b, &v);

	if(((v - b) % (a - b)) == 0) {
		printf("%d\n", ((v - b) / (a - b))); 
	}
	else {
		printf("%d\n", ((v - b) / (a - b)) + 1); 
	}

	return 0;
}
