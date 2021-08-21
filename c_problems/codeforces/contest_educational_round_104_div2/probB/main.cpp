//for testcase 
//1
//5 6
//ans => 3
//output => 4
//doesn't make sense.


#include <stdio.h>
#include <iostream>
#include <stdlib.h>

using namespace std;

int t;
int n, k;

int main()
{
	cin >> t;
	for(int i = 0; i < t; i++) {
		cin >> n >> k;	

		if(n % 2 == 0) {
			if(k % n == 0) {
				cout << n << endl;	
			}
			else cout << (k % n) << endl;
		}
		else {
			long long int cycle;		

			cycle = (long long int)k % ((long long int)(n - 1) + (long long int)(n - 2) * (long long int)(n / 2));

			if(cycle == 0) {
				cout << (n - 1) << endl;
			}
			else {
				if(cycle <= (n - 1)) {
					if(cycle <= (n / 2)) cout << cycle << endl;
					else cout << (cycle + 1) << endl;
				}
				else {
					long long int q, r;

					q = (cycle - n + 1) / (n - 2);
					r = (cycle - n + 1) % (n - 2);

					if(r == 0) {
						q--;
						r = (n - 2);
					}
					
					if(q == 0) {
						if(r <= q) {
							cout << r << endl;
						}
						else if(((n / 2) + q + 1) > r) {
							cout << (r + 1) << endl;
						}
						else {
							cout << (r + 2) << endl;
						}
					}
					else {
						if(r <= q) {
							cout << r << endl;
						}
						else if(((n / 2) + q) > r) {
							cout << (r + 1) << endl;
						}
						else {
							cout << (r + 2) << endl;
						}
					}

				}
			}
		}
	}

	return 0;
}
