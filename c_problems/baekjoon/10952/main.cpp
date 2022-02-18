#include <stdio.h>
#include <iostream>

using namespace std;

int main()
{
	int input1, input2;

	while(1) {
		scanf("%d %d", &input1, &input2);

		if(input1 == 0) break;

		cout << (input1 + input2) << endl;
	}
    
    return 0;
}
