#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>

using namespace std;

int N;
int binaryn[35];
int bosoo[35];

int find_max_power(int tar)
{
	int power = 31;

	while(power >= 0) {
		if(tar >= pow(2, power)) {
			return power;	
		}	

		power--;
	}

	return -1;
}

int main()
{
	cin >> N;		

	int cur;
	cur = N;

	for(int i = 0; i <= 31; i++) {
		binaryn[i] = 0;
	}

	while(1) {
		if(cur == 0) break;	

		int cur_pow;
		cur_pow = find_max_power(cur);

		binaryn[cur_pow] = 1;	

		cur -= pow(2, cur_pow);
	}		

	for(int i = 0; i <= 31; i++) {
		bosoo[i] = (binaryn[i] == 1) ? 0 : 1;
	}

	bosoo[0]++;

#ifdef DEBUG
	for(int i = 0; i <= 31; i++) {
		cout << bosoo[i] << " ";
	}
	cout << "\n";
#endif

	if(bosoo[0] == 2) {
		bosoo[0] = 0;
		for(int i = 1; i <= 31; i++) {
			if(bosoo[i] == 0) {
				bosoo[i] = 1;
				break;
			}		
			else {
				bosoo[i] = 0;
			}
		}
	}

#ifdef DEBUG
	for(int i = 0; i <= 31; i++) {
		cout << binaryn[i] << " ";
	}
	cout << "\n";

	for(int i = 0; i <= 31; i++) {
		cout << bosoo[i] << " ";
	}
	cout << "\n";
#endif

	int ans = 0;
	for(int i = 0; i <= 31; i++) {
		if(binaryn[i] != bosoo[i]) ans++;
	}

	cout << ans << endl;

	return 0;
}
