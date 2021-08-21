#include <stdio.h>
#include <iostream>

int main()
{
	FILE *fo = fopen("input4.txt", "w");

	fprintf(fo, "300000\n");

	for(int i = 1; i < 300000; i++) {
		fprintf(fo, "%d %d\n", i, i+1);
	
	}

	return 0;
}
