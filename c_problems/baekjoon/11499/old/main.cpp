#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#include <math.h>

using namespace std;


typedef struct __POINT {
	int x, y;		
}POINT;

int T;
int N, M;
vector<POINT> dots;
POINT target;
//convexhull
stack<POINT> conv;
//dots extracted to make convexhull
vector<POINT> arr;
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


int main()
{		
	cin >> T;

	for(int testcase = 0; testcase < T; testcase++) {
		dots.clear();
		ans = (double)0;

		cin >> N;

		for(int i = 0; i < N; i++) {
			int input1, input2;
			POINT input;

			cin >> input1 >> input2;

			input.x = input1;
			input.y = input2;	

			dots.push_back(input);
		}

		cin >> M;

		for(int i = 0; i < M; i++) {
			int input_k, input_d;

			cin >> input_k >> input_d;			

			arr.clear();
			//when convexhull dots adding --> if there is same coordinate with target, exclude
			if(input_d == 0) {
				target.x = dots[input_k].x;
				target.y = dots[input_k].y;

				arr.push_back(dots[0]);
				for(int j = input_k; j < N; j++) {
					arr.push_back(dots[j]);	
				}
			}
			else {
				if((input_k % 2) == 1) {
					if(dots[input_k].y < dots[(input_k + 1) % N].y) {
						target.x = dots[input_k].x;
						target.y = dots[input_k].y + input_d;
					}
					else {
						target.x = dots[input_k].x;
						target.y = dots[input_k].y - input_d;
					}
				}
				else {
					target.x = dots[input_k].x - input_d;
					target.y = dots[input_k].y;
				}	
					
				arr.push_back(dots[0]);
				arr.push_back(target);
				for(int j = (input_k + 1); j < N; j++) {
					arr.push_back(dots[j]);
				}
			}


			sort(arr.begin() + 1, arr.end()); 

#ifdef DEBUG
			cout << "### this is arr ###\n";
			for(int j = 0; j < arr.size(); j++) {
				cout << arr[j].x << " " << arr[j].y << "\n";
			}
			cout << "\n\n";
#endif

			//find convexhull!
			for(int j = 0; j < arr.size(); j++) {
				if((j == 0) || (j == 1)) {
					conv.push(arr[j]);
					if((arr[j].x == target.x) && (arr[j].y == target.y)) break;
				}
				else {
					POINT dot_ref, dot_mid, dot_end;

					dot_end = arr[j];		

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

					if((arr[j].x == target.x) && (arr[j].y == target.y)) break;
				}
			}	

#ifdef DEBUG
			cout << "### conv is ###\n";
			while(!conv.empty()) {
				cout << conv.top().x << " " << conv.top().y << "\n";
				conv.pop();
			}
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
		
		printf("%.2Lf\n", ans);
	}		


	return 0;
}
