#include <iostream>
#include <cstdio>

using namespace std;

int main()
{
	char input;
	int cnt[30];

	for(int i = 0; i <= 29; i++) cnt[i] = 0;

	while((input = getchar()) != EOF) {
		if((input >= 'A') && (input <= 'Z')) {
			cnt[input - 65]++;
		}	
		else if((input >= 'a') && (input <= 'z')) {
			cnt[(input - 32) - 65]++;
		}	
	}	

	char ans;	
	int max = -1;

	for(int i = 0; i <= 29; i++) {
		if(cnt[i] > max) {
			max = cnt[i];
			ans = i + 65;
		}	
	}	

	int count;
	count = 0;
	for(int i = 0; i <= 29; i++) {
		if(max == cnt[i]) count++;
		
		if(count == 2) {
			cout << "?" << endl;
			return 0;
		}
	}

	cout << ans << endl;

	return 0;
}
