#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

int main()
{
	for(int i = 2; i <= 100; i++) {
		for(int j = 1; j <= 100; j++) {
			cout << i << " " << j << endl;
		}
	}

	return 0;
}
