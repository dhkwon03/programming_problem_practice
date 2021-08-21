#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string>
#include <cstring>

using namespace std;

char a[10005], b[10005];
int ans[10005];
int len_a, len_b;
int idx;
int upper;
int len_max, len_min;
//max_num = 1 : a is max length number, 2 ; b
int max_num;

int calc(int index, int a, int b, int up_num) {
	if((a + b + up_num) >= 10) {
		ans[index] = (a + b + up_num) % 10;
		upper = (a + b + up_num) / 10;
	}
	else {
		ans[index] = a + b + up_num;
		upper = 0;
	}

	return 0;
}

int main()
{
	for(int i = 0; i < 10004; i++) {
		ans[i] = -1;
	}

	scanf("%s %s", a, b);
	
	len_a = strlen(a);					
	len_b = strlen(b);

	//reverse a
	for(int i = 0; i < (len_a / 2); i++) {
		int temp = a[i];
		a[i] = a[len_a - i - 1];
		a[len_a - i - 1] = temp;
	}

	//reverse b
	for(int i = 0; i < (len_b / 2); i++) {
		int temp = b[i];
		b[i] = b[len_b - i - 1];
		b[len_b - i - 1] = temp;
	}


	len_max = max(len_a, len_b);

	if(len_max == len_a) max_num = 1;
	else max_num = 2;

	len_min = min(len_a, len_b);

#ifdef DEBUG
	printf("###len_max = %d, len_min = %d\n", len_max, len_min);
#endif

	idx = 0;
	upper = 0;

	while(idx < len_max) {
		if(idx >= len_min) {
			if(max_num == 1) calc(idx, (a[idx] - '0'), 0, upper);
			else calc(idx, 0, (b[idx] - '0'), upper);
		}
		else {
			calc(idx, (a[idx] - '0'), (b[idx] - '0'), upper);
		}

		idx++;
	}

	if(upper != 0) {
		ans[idx] = upper;
	}

	int ans_end;
	for(ans_end = 0; ans_end < 10003; ans_end++) {
		if(ans[ans_end] == -1) break;
	}

	for(int i = (ans_end - 1); i >= 0; i--) {
		printf("%d", ans[i]);
	}

	printf("\n");
	
	return 0;
}
