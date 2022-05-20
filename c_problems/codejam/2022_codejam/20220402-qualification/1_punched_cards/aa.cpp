#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <math.h>

using namespace std;

int main()
{
	int T;
	int R, C;
		
	scanf("%d", &T);	

	for(int i = 0; i < T; i++) {
		scanf("%d %d", &R, &C);

		printf("Case #%d:\n", (i + 1));
		printf("..+");
		for(int j = 0; j < (C - 1); j++) printf("-+");
		printf("\n");
		printf("..|");
		for(int j = 0; j < (C - 1); j++) printf(".|");
		printf("\n");
		
		for(int j = 0; j < (R - 1); j++) {
			for(int k = 0; k < C; k++) {
				printf("+-");	
			}
			printf("+\n");
			printf("|");

			for(int k = 0; k < C; k++) {
				printf(".|");
			}
			printf("\n");
		}
		
		for(int j = 0; j < C; j++) {
			printf("+-");	
		}
		printf("+\n");
	}

	return 0;
}
