#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#include <math.h>

using namespace std;

typedef struct __POINT {
	int x, y;		
	bool IsTarget;
}POINT;

typedef struct __CONVEX {
	int x, y;		
	long double dist; //distance between right below point (in stack) and this point
}CONVEX;

typedef struct __TARGET {
	int k, d;
}TARGET;

int T;
int N, M;
vector<POINT> dots;
vector<POINT> dots_input;
vector<TARGET> targets;
//convexhull
stack<CONVEX> conv;
long double total_conv_dist;
long double ans = (long double)0;

//cross product ab X ac
long long int cross_product(int pa_x, int pa_y, int pb_x, int pb_y, int pc_x, int pc_y)
{
	return ((long long int)(pb_x - pa_x) * (long long int)(pc_y - pa_y)) - ((long long int)(pb_y - pa_y) * (long long int)(pc_x - pa_x));
}

bool operator ==(POINT ppa, POINT ppb)
{
	return ((ppa.x == ppb.x) && (ppa.y == ppb.y));
}

bool TargetsCompare(TARGET a, TARGET b)
{
	return (a.k != b.k) ? (a.k > b.k) : (a.d > b.d);
}

int AddVertexToConvexhull (POINT cur_point)
{
	CONVEX dot_ref, dot_mid, dot_end;

	while(conv.size() >= 2) {
		dot_mid = conv.top();
		conv.pop();
		dot_ref = conv.top();
		if(cross_product(dot_ref.x, dot_ref.y, dot_mid.x, dot_mid.y, cur_point.x, cur_point.y) > 0) {
			conv.push(dot_mid);
			break;	
		}
		else {
			total_conv_dist -= dot_mid.dist;	
		}
	}

	dot_end.x = cur_point.x;	
	dot_end.y = cur_point.y;	
	dot_end.dist = sqrt(((long double)(dot_end.x - conv.top().x) * (long double)(dot_end.x - conv.top().x) + (long double)(dot_end.y - conv.top().y) * (long double)(dot_end.y - conv.top().y)));	
	conv.push(dot_end);

	total_conv_dist += dot_end.dist;

	return 0;
}

int main()
{		
	cin >> T;

	for(int testcase = 0; testcase < T; testcase++) {
		//initialization
		dots.clear();
		dots_input.clear();
		targets.clear();
		while(!conv.empty()) conv.pop();
		ans = (long double)0;

		cin >> N;

		for(int i = 0; i < N; i++) {
			int input1, input2;
			POINT input;

			cin >> input1 >> input2;

			input.x = input1;
			input.y = input2;	
			input.IsTarget = false;

			dots_input.push_back(input);
		}

		total_conv_dist = 0;

		cin >> M;

		int nxt_input_point = (N - 1);
		dots.push_back(dots_input[0]);

		for(int i = 0; i < M; i++) {
			int input_k, input_d;
			TARGET input;

			cin >> input_k >> input_d;			
		
			input.k = input_k;	
			input.d = input_d;	

			targets.push_back(input);
		}

		sort(targets.begin(), targets.end(), TargetsCompare);	

		for(int i = 0; i < M; i++) {
			POINT target;

			if(targets[i].d == 0) {
				target.x = dots_input[targets[i].k].x;
				target.y = dots_input[targets[i].k].y;
			}
			else {
				if(dots_input[targets[i].k].y == dots_input[((targets[i].k + 1) % N)].y) {
					if(targets[i].k == 0) {
						target.x = dots_input[targets[i].k].x + targets[i].d;
					}
					else {
						target.x = dots_input[targets[i].k].x - targets[i].d;
					}
					target.y = dots_input[targets[i].k].y;
				}
				else {
					if(dots_input[targets[i].k].y < dots_input[((targets[i].k + 1) % N)].y) {
						target.x = dots_input[targets[i].k].x;
						target.y = dots_input[targets[i].k].y + targets[i].d;
					}
					else {
						target.x = dots_input[targets[i].k].x;
						target.y = dots_input[targets[i].k].y - targets[i].d;
					}
				}
			}

			target.IsTarget = true;

			for(int j = nxt_input_point; j > targets[i].k; j--) {
				dots.push_back(dots_input[j]);
			}

			dots.push_back(target);

			if(targets[i].d == 0) nxt_input_point = targets[i].k - 1;
			else nxt_input_point = targets[i].k;
			
		}

		// push rest of dots_input
		for(int i = nxt_input_point; i >= 1; i--) {
			dots.push_back(dots_input[i]);
		}

#ifdef DEBUG
		printf("### dots ###\n");
		for(int i = 0; i < dots.size(); i++) {
			printf("idx : %d -- (%d, %d) IsTarget? : %d\n", i, dots[i].x, dots[i].y, dots[i].IsTarget); 	
		}
		printf("------\n");
#endif
	

		CONVEX init_dots;
		init_dots.x = dots[0].x;
		init_dots.y = dots[0].y;
		init_dots.dist = 0;

		conv.push(init_dots);
		for(int i = 1; i < dots.size(); i++) {
			AddVertexToConvexhull(dots[i]);
			if(dots[i].IsTarget == true) {
				ans += total_conv_dist;
			}
#ifdef DEBUG
			printf("### cur conv (dots idx = %d)###\n", i);
			stack<CONVEX> temp;
			while(!conv.empty()) {
				cout << conv.top().x << " " << conv.top().y << " / dist : " << conv.top().dist << "\n";
				temp.push(conv.top());
				conv.pop();
			}

			while(!temp.empty()) {
				conv.push(temp.top());
				temp.pop();
			}

			printf("\ntotal_conv_dist : %.1Lf\n--------\n", total_conv_dist);
#endif
		}

		printf("%.1Lf\n", ans);
	}		


	return 0;
}
