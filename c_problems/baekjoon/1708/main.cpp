#include <iostream>
#include <algorithm>
#include <stack>
#include <math.h>

using namespace std;

typedef struct __COORD {
	int x, y;
}COORD;

int N;
COORD dots[100005];
//index of dots which compose convexhull
stack<int> convexhull;

//cross product : AB X AC
long long int cross_product(int ax, int ay, int bx, int by, int cx, int cy)
{
	return ((long long int)(bx - ax) * (long long int)(cy - ay)) - ((long long int)(by - ay) * (long long int)(cx - ax));
}

bool compare(COORD a, COORD b)
{
	long long int value = cross_product(dots[0].x, dots[0].y, a.x, a.y, b.x, b.y);
	if(value > 0) return true;
	else if(value < 0) return false;
	else {
		if(a.y != b.y) return (a.y < b.y);
		else return (a.x < b.x);
	}
}

bool compare_ref(COORD a, COORD b)
{
	if(a.y != b.y) return (a.y < b.y);
	else return (a.x < b.x);
}

int main()
{
	cin >> N;							

	//find min y_coord dot (if same, min x_coord dot)
	for(int i = 0; i < N; i++) {
		cin >> dots[i].x >> dots[i].y;
	}	
	
	sort(dots, dots + N, compare_ref);
	//sort by angle 
	sort(dots + 1, dots+N, compare);

#ifdef DEBUG
	cout << "### sorted dots\n" << endl;
	for(int i = 0; i < N; i++) {
		cout << dots[i].x << " " << dots[i].y << "\n";
	}
	cout << "\n";
#endif

	convexhull.push(0);
	convexhull.push(1);

	for(int i = 2; i < N; i++) {
		//ab X ac
		int dot_a, dot_b, dot_c;
		dot_c = i;
		//if size is lower than 2 --> it means that it is straight line
		while(convexhull.size() >= 2) {
			dot_b = convexhull.top();
			convexhull.pop();
			dot_a = convexhull.top();	

			//ccw (also not straight line)
			if(cross_product(dots[dot_a].x, dots[dot_a].y, dots[dot_b].x, dots[dot_b].y, dots[dot_c].x, dots[dot_c].y) > 0) {
				convexhull.push(dot_b);
				break;				
			}	
		}

		convexhull.push(dot_c);
	}
			
	/*
	convexhull.push(0);				
	
	
	//current end point index
	int cur_end;

	int dota, dotb, dotc;
	dota = 0;
	dotb = 1; 
	dotc = 2;
	//if first 3 points are on straight line...
	while(1) {
		if(cross_product(dots[dota].x, dots[dota].y, dots[dotb].x, dots[dotb].y, dots[dotc].x, dots[dotc].y) > 0) {
			convexhull.push(dotb);
			convexhull.push(dotc);	
			cur_end = dotc;
			break;
		}

		dotb = dotc;
		dotc++;
	}

#ifdef DEBUG
	cout << "### checkpoint! \n" << endl;
	cout << "dota : " << dota << "\n" << "dotb : " << dotb << "\n" << "dotc : " << dotc << "\n";
	cout << "\n";
#endif


	while(cur_end != 0) {
		cur_end++;
		if(cur_end == N) cur_end = 0;

		int dotmid, dotref;
		//check dotref -> dotmid -> cur_end is convex
		//if not, remove the point which is not involved in convexhull
		dotmid = convexhull.top();
		convexhull.pop();
		dotref = convexhull.top();	

		while(1) {
			if(cross_product(dots[dotref].x, dots[dotref].y, dots[dotmid].x, dots[dotmid].y, dots[cur_end].x, dots[cur_end].y) > 0) break;

			dotmid = dotref;
			convexhull.pop();
			dotref = convexhull.top();	
		}

		convexhull.push(dotmid);
		convexhull.push(cur_end);
	}
	*/

	cout << convexhull.size() << endl;

#ifdef DEBUG
	cout << "convexhull is...\n";
	while(!convexhull.empty())
	{
		cout << convexhull.top() << "\n";	
		convexhull.pop();
	}
	cout << "\n" << endl;
#endif

	return 0;
}
