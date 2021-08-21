#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

using namespace std;

int main()
{
	int n, q, k;
	int arr[100005];
	//dp[i][0] : if there is no number at front, count of number that can be exchanged 
	//dp[i][1] : original count of number that can be exchanged in original array 
	//dp[i][2] : if there is no number at back, count of number that can be exchanged 
	int dp[100005][3];
	//sum of sub interval of value dp[i][1]
	long long int subsum[100005];
	int l, r;

	cin >> n >> q >> k;

	for(int i = 1; i <= n; i++) {
		cin >> arr[i];
	}	
	
	if(n != 1) {
		dp[1][0] = arr[2] - 2; 
		dp[1][1] = 0;
		dp[1][2] = (k - 1);
		dp[n][0] = (k - 1);
		dp[n][1] = 0;
		dp[n][2] = k - arr[n - 1] - 1;
		for(int i = 2; i < n; i++) {
			dp[i][0] = arr[i + 1] - 2;	
			dp[i][1] = arr[i + 1] - arr[i - 1] - 2;
			dp[i][2] = k - arr[i - 1] - 1;
		}
#ifdef DEBUG
		cout << "###debug_dp check###\n";
		for(int i = 1; i <= n; i++) {
			cout << dp[i][0] << " " << dp[i][1] << " " << dp[i][2] << "\n";	
		}
		cout << "\n";
#endif
		subsum[1] = 0;
		for(int i = 2; i <= n; i++) {
			subsum[i] = subsum[i - 1] + dp[i][1];   
		}
#ifdef DEBUG
		cout << "###debug_sub check###\n";
		for(int i = 1; i <= n; i++) {
			cout << subsum[i] << "\n";	
		}
		cout << "\n";
#endif

		for(int i = 0; i < q; i++) {
			cin >> l >> r; 

			cout << (dp[l][0] + dp[r][2] + subsum[r - 1] - subsum[l]) << "\n";
		}
	}
	else {
		for(int i = 0; i < q; i++) {
			cin >> l >> r;

			cout << (k - 1);
		}
	}

	return 0;
}
