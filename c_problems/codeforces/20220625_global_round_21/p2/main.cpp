#include <stdio.h>
#include <math.h>

using namespace std;

int T;
int n;

int main()
{
	scanf("%d", &T);

	for(int i = 0; i < T; i++) {
		scanf("%d", &n);

		int ans = 0;
		int not_zero;
		for(int j = 0; j < n; j++) {
			int input;

			scanf("%d", &input);

			if(j == 0) {
				if(input == 0) {
					not_zero = 0;
				}
				else {
					not_zero = 1;
					ans++;
				}
			}
			else {
				if((not_zero == 0) && (input != 0)) {
					ans++;
					not_zero = 1;
				}
				
				if(input == 0) {
					not_zero = 0;
				}
			}
		}

		if(ans >= 2) ans = 2;

		printf("%d\n", ans);
	}

	return 0;
}
