#include <stdio.h>
#include <stdlib.h>
#include <math.h>

using namespace std;

int main()
{
	int x;

	scanf("%d", &x);

	int layer_idx = 1;

	while(1) {
		if(((((layer_idx - 1) * layer_idx) / 2) < x) && ((((layer_idx + 1) * layer_idx) / 2) >= x)) {
			break;	
		}

		layer_idx++;
	}

	int remain;

	remain = x - (((layer_idx - 1) * layer_idx) / 2);

	// denominator, numerator
	int deno, numer;

	if((layer_idx % 2) == 1) {
		numer = layer_idx - remain + 1;	
		deno = remain;
	}
	else {
		numer = remain;
		deno = layer_idx - remain + 1;
	}

	printf("%d/%d\n", numer, deno); 

	return 0;
}
