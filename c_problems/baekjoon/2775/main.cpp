#include <stdio.h>
#include <stdlib.h>
#include <math.h>

using namespace std;


int main()
{
    	int t;
	int k, n;
	int ans;

	scanf("%d", &t);

	for(int i = 0; i < t; i++) {
		scanf("%d %d", &k, &n);

		if(n == 1) {
			ans = (n + 1) * n / 2;		
		}
		else {
		    	int combination = 1;
			ans = 0;
#ifdef DEBUG
			printf("###combination for each step###\n");
#endif
			for(int j = 1; j <= n; j++) {
				if(j != 1) {
					combination = combination * (k + j - 2) / (j - 1);	
				}
#ifdef DEBUG
				printf("### j = %d, combination = %d\n", j, combination);
#endif

				ans += (n - j + 1) * combination;
			}
		}

		printf("%d\n", ans);
#ifdef DEBUG
		printf("\n\n");
#endif
	}

	return 0;
}
