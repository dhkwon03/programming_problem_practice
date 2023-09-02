#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <math.h>

int main()
{
	int N, M;
	int arr[55][55];
	//B = 1, W = 0

	scanf("%d %d", &N, &M);

	for(int i = 0; i < N; i++) {
		for(int j = 0; j < M; j++) {
			char input;	
			scanf(" %c", &input); 

			if(input == 'W') arr[i][j] = 0;
			else if(input == 'B') arr[i][j] = 1;
		}
	}	

#ifdef DEBUG
	for(int i = 0; i < N; i++) {
		for(int j = 0; j < M; j++) {
			printf("%d ", arr[i][j]);
		}
		printf("\n");
	}	

	printf("\n\n");
#endif
	


	int ans = 100;
	for(int i = 0; i <= (N - 8); i++) {
		for(int j = 0; j <= (M - 8); j++) {
			int cntw, cntb;
			cntw = cntb = 0;

			for(int k = 0; k < 8; k++) {
				for(int l = 0; l < 8; l++) {
					if((k % 2) == 0) {
						if((l % 2) == 0) {
							if(arr[i+k][j+l] != 0) cntw++;
							else cntb++;
						}
						else {
							if(arr[i+k][j+l] != 0) cntb++;
							else cntw++;
						}
					}
					else {
						if((l % 2) == 0) {
							if(arr[i+k][j+l] != 0) cntb++;
							else cntw++;
						}
						else {
							if(arr[i+k][j+l] != 0) cntw++;
							else cntb++;
						}
					}	
				}
			}	

			ans = std::min(ans, cntw);	
			ans = std::min(ans, cntb);	
		}
	}

	printf("%d\n", ans);

	return 0;
}
