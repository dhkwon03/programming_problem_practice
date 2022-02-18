#include <iostream>
#include <cstdio>

using namespace std;

int main()
{
	int N;
	int arr[1005];
	int max;
	

	cin >> N;

	for(int i = 0; i < N; i++) {
		cin >> arr[i];
	}

	max = 0;	

	int sum = 0;

	for(int i = 0; i < N; i++) {
		if(max < arr[i]) max = arr[i];
		
		sum += arr[i];
	}	

	double ans;

	ans = ((double)sum / (double)max) * 100.0 / (double)N; 	

	printf("%.6f\n", ans);

	return 0;
}
