#include <stdio.h>
#include <algorithm>

int main()
{
	int N;

	scanf("%d", &N);

	int cnt_two = 0;
	int cnt_five = 0;

	for(int i = 1; i <= N; i++) {
		int temp;
	
		temp = i;

		while(temp % 2 == 0) {
			if(temp % 2 == 0) cnt_two++;

			temp = temp / 2;
		}

		temp = i;

		while(temp % 5 == 0) {
			if(temp % 5 == 0) cnt_five++;

			temp = temp / 5;
		}
	}	

	printf("%d\n", std::min(cnt_two, cnt_five));

	return 0;
}
