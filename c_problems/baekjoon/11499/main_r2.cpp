#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#include <math.h>

using namespace std;


typedef struct __POINT {
	int x, y;		
	int idx;
}POINT;

int T;
int N, M;
vector<POINT> dots;
vector<POINT> dots_input;
POINT target;
//convexhull
stack<POINT> conv;
long double ans = (long double)0;

//cross product ab X ac
long long int cross_product(POINT pa, POINT pb, POINT pc)
{
	return ((long long int)(pb.x - pa.x) * (long long int)(pc.y - pa.y)) - ((long long int)(pb.y - pa.y) * (long long int)(pc.x - pa.x));
}

bool operator <(POINT ppa, POINT ppb)
{
	long long int value = cross_product(dots[0], ppa, ppb);

	if(value > 0) return true;
	else if(value < 0) return false;
	else {
		if(ppa.y != ppb.y) return (ppa.y < ppb.y);
		else return (ppa.x < ppb.x);
	}

}

bool compare (POINT ca, POINT cb)
{
	return (ca < cb);
}


int main()
{		
	cin >> T;

	for(int testcase = 0; testcase < T; testcase++) {
		dots.clear();
		dots_input.clear();
		ans = (double)0;

		cin >> N;

		for(int i = 0; i < N; i++) {
			int input1, input2;
			POINT input;

			cin >> input1 >> input2;

			input.x = input1;
			input.y = input2;	
			input.idx = i;

			dots.push_back(input);
			dots_input.push_back(input);
		}

		sort(dots.begin() + 1, dots.end(), compare);
#ifdef DEBUG
		cout << "### dots after sorting ###\n";
		for(int i = 0; i < N; i++) {
			cout << dots[i].x << " " << dots[i].y << "\n";
		}

		cout << "\n\n";
#endif

		cin >> M;

		for(int i = 0; i < M; i++) {
			int input_k, input_d;
			int range_st, range_end;

			cin >> input_k >> input_d;			

			//when convexhull dots adding --> if there is same coordinate with target, exclude
			if(input_d == 0) {
				target.x = dots_input[input_k].x;
				target.y = dots_input[input_k].y;

				int flag = 0;
				for(int j = 1; j < N; j++) {
					if((flag == 0) && (dots[j].idx >= input_k)) { 
						range_st = j;
						flag = 1;
					}
					else if((flag == 1) && (target < dots[j])) {
						range_end = j - 1;
						break;
					}
				}
			}
			else {
				if((input_k % 2) == 1) {
					if(dots_input[input_k].y < dots_input[(input_k + 1) % N].y) {
						target.x = dots_input[input_k].x;
						target.y = dots_input[input_k].y + input_d;
					}
					else {
						target.x = dots_input[input_k].x;
						target.y = dots_input[input_k].y - input_d;
					}
				}
				else {
					target.x = dots_input[input_k].x - input_d;
					target.y = dots_input[input_k].y;
				}	
					
				int flag = 0;
				for(int j = 1; j < N; j++) {
					if((flag == 0) && (dots[j].idx >= (input_k + 1))) { 
						range_st = j;
						flag = 1;
					}
					else if((flag == 1) && (target < dots[j])) {
						range_end = j - 1;
						break;
					}
				}
			}

#ifdef DEBUG
			cout << "###checkpoint###\n";
			cout << "range_st = " << range_st << "\n";
			cout << "range_end = " << range_end << "\n";
			cout << "target = (" << target.x << " " << target.y << ")\n\n";
#endif




			//find convexhull!
			conv.push(dots[0]);
			if((dots[0].x != target.x) || (dots[0].y != target.y)) { 
				for(int j = range_st; j <= range_end; j++) {
					if(((input_d == 0) && (dots[j].idx < input_k)) || ((input_d != 0) && (dots[j].idx < (input_k + 1)))) continue;

					POINT dot_ref, dot_mid, dot_end;

					dot_end = dots[j];		

					while(conv.size() >= 2) {
						dot_mid = conv.top();
						conv.pop();
						dot_ref = conv.top();
						if(cross_product(dot_ref, dot_mid, dot_end) > 0) {
							conv.push(dot_mid);
							break;	
						}
					}

					conv.push(dot_end);
				}	

				//for last point
				POINT dot_1, dot_2, dot_3;

				dot_3 = target;		

				while(conv.size() >= 2) {
					dot_2 = conv.top();
					conv.pop();
					dot_1 = conv.top();
					if(cross_product(dot_1, dot_2, dot_3) > 0) {
						conv.push(dot_2);
						break;	
					}
				}

				conv.push(dot_3);
			}

#ifdef DEBUG
			cout << "### conv is ###\n";
			stack<POINT> temp;
			while(!conv.empty()) {
				cout << conv.top().x << " " << conv.top().y << "\n";
				temp.push(conv.top());
				conv.pop();
			}

			conv = temp;
			cout << "\n\n";
#endif


			//pop all of conv contents when calculating distances
			POINT prev_conv;
			POINT cur_conv;
			prev_conv = conv.top();
			conv.pop();
			while(!conv.empty()) {
				cur_conv = conv.top();

				ans += sqrt((((long double)(cur_conv.x - prev_conv.x) * (long double)(cur_conv.x - prev_conv.x)) + ((long double)(cur_conv.y - prev_conv.y) * (long double)(cur_conv.y - prev_conv.y))));			
				prev_conv = cur_conv;
				conv.pop();
			}
		}
		
		printf("%.1Lf\n", ans);
	}		


	return 0;
}
