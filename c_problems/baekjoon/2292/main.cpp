#include <stdio.h>
#include <stdlib.h>
#include <math.h>

using namespace std;

int main()
{
	int num;

	scanf("%d", &num);

	if(num == 1) printf("1\n");
	else {
	    	int n = 2;
		while(1) {
			if(((3*pow(n, 2) - 9 * n + 8) <= num) && ((1 + 3*pow(n, 2) - 3*n) >= num)) {
				break;
			}
			
			n++;
		}

		printf("%d\n", n);
	}

	return 0;
}
