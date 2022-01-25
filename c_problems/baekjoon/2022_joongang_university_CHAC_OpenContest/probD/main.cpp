#include <iostream>

using namespace std;

char input[10];
int mini;
int seco;
int target;
int ans = 0;

int main()
{
	cin >> input;	

	mini = (input[0] - '0') * 10 + (input[1] - '0');	
	seco = (input[3] - '0') * 10 + (input[4] - '0');	

	target = mini * 60 + seco;		

	int cur;

	cur = target;

	while(1) {
		if(cur <= 600) {
			ans++;
			cur -= 600;
		}	
		else if(cur <= 60) {
			ans++;
			cur -= 60;
		}	
		else if(cur <= 10) {
			ans++;
			cur -= 10;
		}	
	}	


	
	
	return 0;
}
