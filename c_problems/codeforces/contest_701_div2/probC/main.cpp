#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

using namespace std;

int t;

int x, y;

long long int ans;

int main()
{
	cin >> t;

	for(int i = 0; i < t; i++) {
		cin >> x >> y;

		ans = 0;		

		for(int j = 2; j <= min(x, y); j++) {

			ans += (min(x,(j * (j + 1) - 1)) / (j + 1));

		}

		cout << ans << "\n";
	}
	
}
