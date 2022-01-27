#include <iostream>
#include <math.h>

using namespace std;

typedef struct __COORD {
	double x, y;	
}COORD;

int N;
COORD polygon[100005];
double area;
double ans;
double n1, n2, n3;

double cross_product(double ax, double ay, double bx, double by) {
	return ((ax * by) - (ay * bx));
}

double expectation_calc(double xi, double yi, double xii, double yii)
{
	n1 += ((xii*xii + xi * xi) * (xii + xi) * (yii - yi) - (yii * yii + yi * yi) * (yii + yi) * (xii - xi));
	n2 += (xii * xii + xi * xii + xi * xi) * (yii - yi);
	n3 += (yii * yii + yi * yii + yi * yi) * (xii - xi);

	return 0;
}

int main()
{
	cin >> N;	

	for(int i = 0; i < N; i++) {
		scanf("%lf %lf", &polygon[i].x, &polygon[i].y);
	}

	area = 0;
	//calculate area
	for(int i = 1; i < (N - 1); i++) {
		area += 0.5 * cross_product((polygon[i].x - polygon[0].x), (polygon[i].y - polygon[0].y), (polygon[i + 1].x - polygon[0].x), (polygon[i + 1].y - polygon[0].y));
	}	

	n1 = 0;
	n2 = 0;
	n3 = 0;
	for(int i = 0; i < (N - 1); i++) {
		expectation_calc(polygon[i].x, polygon[i].y, polygon[i + 1].x, polygon[i + 1].y);	
	}	

	expectation_calc(polygon[N - 1].x, polygon[N - 1].y, polygon[0].x, polygon[0].y);

	ans = ((double)1.0 / (double)6.0) * ((double)1.0 / area) * n1 - ((double)1.0 / (double)18.0) * ((double)1.0 / (area * area)) * (n2 * n2 + n3 * n3);

	printf("%.12lf\n", ans);

	return 0;
}
