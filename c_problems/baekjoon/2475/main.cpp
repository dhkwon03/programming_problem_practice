#include <iostream>
#include <cstdio>

using namespace std;

int main()
{
	int sum = 0;

	for(int i = 0; i < 5; i++) {
		int input;
		cin >> input;
	
		sum += input * input;
	}

	cout << (sum % 10) << endl;


	return 0;
}
