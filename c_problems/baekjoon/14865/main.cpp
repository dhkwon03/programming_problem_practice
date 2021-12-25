#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <stack>
#include <vector>
#include <iostream>
#include <math.h>

using namespace std;

typedef struct __BONGURI {
	long long int l, r;
}BONGURI;

int N;
stack<BONGURI> st;
vector<BONGURI> arr;
long long int input_seq[1000005][2];
long long int ans1, ans2;

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

	for(int i = 0; i < N; i++) {
		cin >> input_seq[i][0] >> input_seq[i][1];
	}

	int idx;
	idx = 0;
	if(input_seq[0][1] > 0) {
		idx = N - 1;
		while(input_seq[idx][1] > 0) {
			idx--;	
		}
	}

	int flag = 0;
	long long int bong1, bong2;
	for(long long int i = idx; i <= (idx + N); i++) {
		long long int index = (i % N);
		if((flag == 0) && (input_seq[index][1] > 0)) {
			flag = 1;
			bong1 = input_seq[index][0];
		}
		else if((flag == 1) && (input_seq[index][1] < 0)) {
			flag = 0;
			bong2 = input_seq[index][0];

			BONGURI input;
			input.l = min(bong1, bong2);
			input.r = max(bong1, bong2);

			arr.push_back(input);
		}
	}

	sort(arr.begin(), arr.end(), compare);

	ans1 = 0;
	ans2 = 1;

	for(vector<BONGURI>::iterator it = arr.begin(); it != arr.end(); it++) {
		if(st.empty()) {
			st.push(*it);
			ans1++;
		}
		else if(!is_inside(st.top(), *it)) {
			ans2++;
		
			while(!is_inside(st.top(), *it)) { 
				st.pop();

				if(st.empty()) {
					ans1++;
					break;
				}
			}
			st.push(*it);
		}
		else if(is_inside(st.top(), *it)) {
			st.push(*it);
		}
	}


	printf("%lld %lld\n", ans1, ans2);

	return 0;
}
