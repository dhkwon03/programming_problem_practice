#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include <math.h>
#include <vector>

using namespace std;

typedef struct __RANGE {
	int endnum;
	int diff;
	int rsize;
}RANGE;

vector<RANGE> range;	
vector<int> s;
int ans = 0;

bool compare(int a, int b) { return (a > b); }

int solve(int r_idx, int extra, int cur_len)
{

	
}

int main()
{
	int T;

	scanf("%d", &T);	

	for(int i = 0; i < T; i++) {
		int N;
		scanf("%d", &N);

		for(int j = 0; j < N; j++) {
			int s_input;
			scanf("%d", &s_input);
			s.push_back(s_input);
		}

		sort(s.begin(), s.end(), compare);

		int prev = s[0];

		int count = 0;
		for(int j = 0; j < N; j++) {
			if(prev == s[j]) count++;
			else {
				RANGE input;
				input.endnum = prev;
				input.diff = count;
				input.rsize = 0;
				range.push_back(input); 
				prev = s[j];
				count = 1;
			}
		}

		RANGE input;
		input.endnum = s[N-1];
		input.cnt = N;
		input.diff = count;
		input.rsize = 0;

		range.push_back(input);

		for(int j = 0; j < range.size(); j++) {
			if(j == 0) range[j].rsize = range[j].endnum;
			else range[j].rsize = range[j].endnum - range[j - 1].endnum;

			range[j].diff = range[j].diff - range[j].rsize;
		}

		reverse(range.begin(), range.end());

		/*
		int ans = 0;
		int cur_len = 0;
		for(int j = 0; j < range.size(); j++) {

			if(j == 0) {
				if(range[j].cnt >= range[j].endnum) {
					cur_len += range[j].endnum;
				}
				else {
					ans = max(ans, (cur_len + range[j].cnt));
					cur_len = range[j].cnt;
				}
			}	
			else {
				if(range[j].cnt >= (range[j].endnum - range[j - 1].endnum)) {
					cur_len += (range[j].endnum - range[j - 1].endnum);
				}
				else {
					ans = max(ans, (cur_len + range[j].cnt));
					cur_len = range[j].cnt;
				}
			}	

			if(cur_len >= N) {
				cur_len = N;
				break;				
			}
		}	

		printf("Case #%d: %d\n", (i + 1), max(ans, cur_len));
		*/

	}

	return 0;
}
