#include <iostream>
#include <algorithm>

using namespace std;

typedef struct __POINT {
	int x, y;
}POINT;

int N;
POINT arr[100005];

bool operator< (POINT pa, POINT pb)
{
	if(pa.x != pb.x) return (pa.x < pb.x);
	else return (pa.y < pb.y);
}

bool compare(POINT a, POINT b)
{
	return (a < b);
}

int main()
{

	cin >> N;

	for(int i = 0; i < N; i++) {
		cin >> arr[i].x >> arr[i].y;
	}

	sort(arr, arr+N, compare);

	for(int i = 0; i < N; i++) {
		cout << arr[i].x << " " << arr[i].y << "\n";
	}

	return 0;
}
