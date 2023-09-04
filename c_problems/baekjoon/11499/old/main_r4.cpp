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

bool operator ==(POINT ppa, POINT ppb)
{
	return ((ppa.x == ppb.x) && (ppa.y == ppb.y));
}

bool compare (POINT ca, POINT cb)
{
	return (ca < cb);
}

int FindIdxOfTarget_onDots()
{
	int low, high, mid;

	low = 1;
	high = N - 1;

	while(low < high) {
		mid = (low + high) / 2;

		if(dots[mid] < target) low = mid + 1;
		else high = mid - 1;
	}

	return low;
}

int AddVertexToConvexhull (POINT dot_end)
{
	POINT dot_ref, dot_mid;

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

	return 0;
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

			cin >> input_k >> input_d;			

			//when convexhull dots adding --> if there is same coordinate with target, exclude
			if(input_d == 0) {
				target.x = dots_input[input_k].x;
				target.y = dots_input[input_k].y;
			}
			else {
				if(dots_input[input_k].y == dots_input[((input_k + 1) % N)].y) {
					target.x = dots_input[input_k].x - input_d;
					target.y = dots_input[input_k].y;
				}
				else {
					if(dots_input[input_k].y < dots_input[((input_k + 1) % N)].y) {
						target.x = dots_input[input_k].x;
						target.y = dots_input[input_k].y + input_d;
					}
					else {
						target.x = dots_input[input_k].x;
						target.y = dots_input[input_k].y - input_d;
					}
				}
				/*
				if((input_k % 2) == 1) {
					if(dots_input[input_k].y < dots_input[((input_k + 1) % N)].y) {
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
				*/
			}

			int target_idx;

			//target_idx = i --> dots[i] <= target < dots[i+1]
			//binary search to find the target_idx satisfying dots[i] <= target < dots[i+1]
			target_idx = FindIdxOfTarget_onDots();

#ifdef DEBUG
			printf("target = %d %d, target idx = %d\n", target.x, target.y, target_idx);
#endif

			int cur_idx;		
			POINT prev_point;

			//state_same_slope --> if 1 : in the middle of sequence of points that have same slope (among the point that satisfies idx > input_k) 
			bool state_same_slope;

			POINT dot_ref, dot_mid, dot_end;

			//find convexhull -- Graham's scan
			conv.push(dots[0]);

			if((dots[0].x != target.x) || (dots[0].y != target.y)) { 
				cur_idx = 1;
				prev_point = dots[0];
				state_same_slope = false;
				while(cur_idx < N) {
					if(cur_idx == target_idx) {
						if((prev_point == target) && (state_same_slope == false)) {
							state_same_slope = true;
							conv.pop();
							AddVertexToConvexhull(target);
						}
						else if(!(prev_point == target)) {
							if(state_same_slope == true) {
								state_same_slope = false;

								//have to add prev_point to convexhull	
								AddVertexToConvexhull(prev_point);
							}

							//add cur_idx point to convexhull
							AddVertexToConvexhull(target);
						}

						break;
					}
					else {
						if(dots[cur_idx].idx > input_k) {
							if((prev_point == dots[cur_idx]) && (state_same_slope == false)) {
								state_same_slope = true;
								conv.pop();
							}
							else if(!(prev_point == dots[cur_idx])) {
								if(state_same_slope == true) {
									state_same_slope = false;

									//have to add prev_point to convexhull	
									AddVertexToConvexhull(prev_point);
								}

								//add cur_idx point to convexhull
								AddVertexToConvexhull(dots[cur_idx]);
							}

							prev_point = dots[cur_idx];
						}

						cur_idx++;
					}
				}	
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
