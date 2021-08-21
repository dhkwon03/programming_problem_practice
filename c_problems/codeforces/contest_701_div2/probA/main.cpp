#include <iostream>
#include <stdio.h>
#include <math.h>

using namespace std;

int t;
int a, b;

int count_division(int n1, int n2)
{
	int cnt;

	cnt = 0;
	while(1) {
		if(n1 == 0) break;

		n1 /= n2;
		cnt++;
	}

	return cnt;
}

int main()
{
	int ans; 

	cin >> t;

	for(int i = 0; i < t; i++) {
		cin >> a >> b;

		int ans;

		ans = 0;

		if(b == 1) {
			b++;
			ans++;
		}
		
		while(1) {
			if((a / b) == 0) {
				ans++;	
				break;
			}
			
			if(count_division((a / b), b) < count_division(a, b + 1)) {
				a /= b;
			}
			else {
				b++;
			}

			ans++;
		}

		cout << ans << "\n";
	}	

	

	return 0;
}
