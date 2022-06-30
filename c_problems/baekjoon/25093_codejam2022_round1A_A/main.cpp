#include <stdio.h>
#include <math.h>
#include <string.h>

int main()
{
	int T;

	scanf("%d", &T);

	for(int i = 0; i < T; i++) {
		char arr[105];
			
		scanf("%s", arr);

		int len_arr = strlen(arr);
		char prev = 0;
		int prev_cnt = 0;
		printf("Case #%d: ", (i + 1));
		for(int j = 0; j < len_arr; j++) {
			if(prev == 0) {
				prev = arr[j];
				prev_cnt = 1;
			}
			else {
				if(arr[j] > prev) {
					for(int k = 0; k < (prev_cnt * 2); k++) {
						printf("%c", prev);	
					}
					prev_cnt = 1;
					prev = arr[j];
				}
				else if(arr[j] < prev) {
					for(int k = 0; k < prev_cnt; k++) {
						printf("%c", prev);	
					}
					prev_cnt = 1;
					prev = arr[j];
				}
				else {
					prev_cnt++;
				}
			}
		}

		for(int k = 0; k < prev_cnt; k++) {
			printf("%c", prev);	
		}
		printf("\n");
	}

	return 0;
}
