#include <stdio.h>
#include <iostream>

using namespace std;

int main()
{
	int t, n;
	int arr[105];	
	int min;
	int cnt;

	cin >> t;

	for(int i = 0; i < t; i++) {
		cin >> n;
		min = 10000;	
		for(int j = 0; j < n; j++) {
			cin >> arr[j];

			if(min > arr[j]) min = arr[j];
		}
		cnt = 0;	
		for(int j = 0; j < n; j++) {
			if(min == arr[j]) cnt++; 
		}
		cout << (n - cnt) << endl;	
	}

	return 0;
}
