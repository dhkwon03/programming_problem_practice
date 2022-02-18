#include <stdio.h>
#include <iostream>

using namespace std;

int main()
{
	int input1, input2;

	while(scanf("%d %d", &input1, &input2) != EOF) {
		cout << (input1 + input2) << endl;
	}
    
    return 0;
}
