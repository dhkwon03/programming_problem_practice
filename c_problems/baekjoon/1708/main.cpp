#include <iostream>
#include <algorithm>
#include <math.h>

using namespace std;

typedef struct __COORD {
	int x, y;
}COORD;

int N;
COORD dots[100005];

int main()
{
	cin >> N;							

	for(int i = 0; i < N; i++) {
		cin >> dots[i].x >> dots[i].y;
	}	

	

	return 0;
}
