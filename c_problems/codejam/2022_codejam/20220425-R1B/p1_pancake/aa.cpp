#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <math.h>
#include <deque>

using namespace std;

int T, N;
deque<int> pan;
int ans;

int solve(int prev, int cnt) 
{
	int cur_prev;
	int temp_f, temp_b;

	temp_f = pan.front();
	temp_b = pan.back();

	if(pan.size() == 1) {
		if(prev <= pan.front()) {
			ans = max(ans, cnt + 1);
		}
		else {
			ans = max(ans, cnt);
		}
		
		return 0;
	}

	if(prev > max(pan.front(), pan.back())) {
		if(pan.front() < pan.back()) {
			cur_prev = max(pan.front(), prev);	
			pan.pop_front();	
			solve(cur_prev, cnt);
			pan.push_front(temp_f);
		}
		else if(pan.front() == pan.back()) {
			cur_prev = max(pan.front(), prev);	
			pan.pop_front();	
			solve(cur_prev, cnt);
			pan.push_front(temp_f);
			cur_prev = max(pan.back(), prev);	
			pan.pop_back();
			solve(cur_prev, cnt);
			pan.push_back(temp_b);
		}
		else {
			cur_prev = max(pan.back(), prev);	
			pan.pop_back();	
			solve(cur_prev, cnt);
			pan.push_back(temp_b);
		}
	}
	else if(prev <= min(pan.front(), pan.back())) {
		if(pan.front() < pan.back()) {
			cur_prev = max(pan.front(), prev);	
			pan.pop_front();	
			solve(cur_prev, cnt + 1);
			pan.push_front(temp_f);
		}
		else if(pan.front() == pan.back()) {
			cur_prev = max(pan.front(), prev);	
			pan.pop_front();	
			solve(cur_prev, cnt + 1);
			pan.push_front(temp_f);
			cur_prev = max(pan.back(), prev);	
			pan.pop_back();
			solve(cur_prev, cnt + 1);
			pan.push_back(temp_b);
		}
		else {
			cur_prev = max(pan.back(), prev);	
			pan.pop_back();	
			solve(cur_prev, cnt + 1);
			pan.push_back(temp_b);
		}
	}
	else {
		if(pan.front() < pan.back()) {
			cur_prev = max(pan.front(), prev);	
			pan.pop_front();	
			solve(cur_prev, cnt);
			pan.push_front(temp_f);
			cur_prev = max(pan.back(), prev);	
			pan.pop_back();
			solve(cur_prev, cnt + 1);
			pan.push_back(temp_b);
		}
		else {
			cur_prev = max(pan.front(), prev);	
			pan.pop_front();	
			solve(cur_prev, cnt + 1);
			pan.push_front(temp_f);
			cur_prev = max(pan.back(), prev);	
			pan.pop_back();
			solve(cur_prev, cnt);
			pan.push_back(temp_b);
		}
	}

	return 0;
}

int main()
{
	scanf("%d", &T);	

	for(int i = 0; i < T; i++) {
		scanf("%d", &N);

		pan.clear();

		for(int j = 0; j < N; j++) {
			int input_val;

			scanf("%d", &input_val);

			pan.push_back(input_val);
		}

		ans = -1;

		solve(-1, 0);		 		

		printf("Case #%d: %d\n", (i + 1), ans);
	}		

	return 0;
}
