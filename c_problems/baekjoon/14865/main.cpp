#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <stack>
#include <vector>
#include <iostream>
#include <math.h>

using namespace std;

typedef struct __BONGURI {
	int l, r;
}BONGURI;

int N;
stack<BONGURI> st;
vector<BONGURI> arr;
int input_seq[1000005][2];
int ans1, ans2;

bool is_inside(BONGURI b1, BONGURI b2)
{
	//is b2 inside b1?
	if((b1.l < b2.l) && (b2.r < b1.r)) return true;
	else return false;
}

bool compare(BONGURI a1, BONGURI a2) 
{
	return (a1.l < a2.l);
}

int main()
{
	cin >> N;

	int flag = 0;
	int bong1, bong2;
	for(int i = 0; i < N; i++) {
		cin >> input_seq[i][0] >> input_seq[i][1];
	}

	int idx1 = (N - 1);
	int idx2 = 0;
	if(input_seq[0][1] > 0) {
		idx1 = N - 1;
		idx2 = 0;
		while(input_seq[idx1][1] > 0) {
			idx1--;	
		}

		while(input_seq[idx2][1] > 0) {
			idx2++;
		}

		BONGURI input_init;
		input_init.l = min(input_seq[idx1][0], input_seq[idx2][0]);
		input_init.r = max(input_seq[idx1][0], input_seq[idx2][0]);

		arr.push_back(input_init);
	}

	for(int i = idx2; i <= idx1; i++) {
		if((flag == 0) && (input_seq[i][1] > 0)) {
			flag = 1;
			bong1 = input_seq[i][0];
		}
		else if((flag == 1) && (input_seq[i][1] < 0)) {
			flag = 0;
			bong2 = input_seq[i][0];

			BONGURI input;
			if(bong1 < bong2) {
				input.l = bong1;
				input.r = bong2;	
			}
			else {
				input.l = bong2;
				input.r = bong1;
			}

			arr.push_back(input);
		}
	}

	sort(arr.begin(), arr.end(), compare);

	ans1 = 0;
	ans2 = 0;

	st.push(arr[0]);
	for(vector<BONGURI>::iterator it = arr.begin() + 1; it != arr.end(); it++) {
		if(!is_inside(st.top(), *it)) ans2++;
		
		while(!is_inside(st.top(), *it)) { 
			st.pop();

			if(st.empty()) {
				ans1++;
				break;
			}
		}
		st.push(*it);
	}

	ans1++;
	ans2++;

	printf("%d %d\n", ans1, ans2);

	return 0;
}
