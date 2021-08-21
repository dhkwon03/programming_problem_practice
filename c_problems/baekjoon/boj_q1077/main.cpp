#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <vector>
#include <math.h>

using namespace std;

typedef struct __DOTS {
	double x, y;
}DOT;

int N, M;

vector<DOT> con1;
vector<DOT> con2;

//intersect line index : value -- (value + 1) -> line
//[0] : con1, [1] : con2
//first intersection line 
int intersect_idx1[2];
//second intersection line
int intersect_idx2[2];

DOT inter1;
DOT inter2;

int flag = 0;

vector<DOT> overlap;

//con1 : k -> l, con2 : m -> n
int intersect_decision(DOT k, DOT l, DOT m, DOT n, int index1, int index2)
{
	double a = k.x;
	double b = k.y;
	double c = l.x;
	double d = l.y;
	double p = m.x;
	double q = m.y;
	double r = n.x;
	double s = n.y;	

	double inter_ans;

#ifdef DEBUG
	printf("###intersect_decision function###\n");
	printf("a = %.10f\n", a);
	printf("b = %.10f\n", b);
	printf("c = %.10f\n", c);
	printf("d = %.10f\n", d);
	printf("p = %.10f\n", p);
	printf("q = %.10f\n", q);
	printf("r = %.10f\n", r);
	printf("s = %.10f\n", s);

	printf("\n\n");
#endif



	if(a == c) {
		if(q == s) {
			inter_ans = a;

			if((min(a, c) <= inter_ans) && (inter_ans <= max(a, c)) && (min(p, r) <= inter_ans) && (inter_ans <= max(p, r))
				&& (min(b, d) <= inter_ans) && (inter_ans <= max(b, d)) && (min(q, s) <= inter_ans) && (inter_ans <= max(q, s))) {
				if(flag == 0) {
					flag = 1;

					inter1.x = inter_ans;

					inter1.y = q;

					intersect_idx1[0] = index1;
					intersect_idx1[1] = index2;
				}
				else {
					inter2.x = inter_ans;

					inter2.y = q;

					intersect_idx2[0] = index1;
					intersect_idx2[1] = index2;
				}
			}
		}
		else if(p != r) {
			inter_ans = ((q - s) * (a - p) / (p - r)) + q;

			if((min(b, d) <= inter_ans) && (inter_ans <= max(b, d)) && (min(q, s) <= inter_ans) && (inter_ans <= max(q, s))) {
				if(flag == 0) {
					flag = 1;

					inter1.x = a;

					inter1.y = inter_ans;

					intersect_idx1[0] = index1;
					intersect_idx1[1] = index2;
				}
				else {
					inter2.x = a;

					inter2.y = inter_ans;

					intersect_idx2[0] = index1;
					intersect_idx2[1] = index2;
				}
			}
		}
	}
	else if(b == d) {
		if(p == r) {
			inter_ans = p;

			if((min(a, c) <= inter_ans) && (inter_ans <= max(a, c)) && (min(p, r) <= inter_ans) && (inter_ans <= max(p, r))
					&& (min(b, d) <= inter_ans) && (inter_ans <= max(b, d)) && (min(q, s) <= inter_ans) && (inter_ans <= max(q, s))) {
				if(flag == 0) {
					flag = 1;

					inter1.x = inter_ans;

					inter1.y = b;

					intersect_idx1[0] = index1;
					intersect_idx1[1] = index2;
				}
				else {
					inter2.x = inter_ans;

					inter2.y = b;

					intersect_idx2[0] = index1;
					intersect_idx2[1] = index2;
				}
			}
		}
		else if(q != s) {
			inter_ans = ((b - q) * (p - r) / (q - s)) + p;

			if((min(a, c) <= inter_ans) && (inter_ans <= max(a, c)) && (min(p, r) <= inter_ans) && (inter_ans <= max(p, r))) {
				if(flag == 0) {
					flag = 1;

					inter1.x = inter_ans;

					inter1.y = b;

					intersect_idx1[0] = index1;
					intersect_idx1[1] = index2;
				}
				else {
					inter2.x = inter_ans;

					inter2.y = b;

					intersect_idx2[0] = index1;
					intersect_idx2[1] = index2;
				}
			}
		}
	}
	else {
		if(p == r) {
			inter_ans = ((b - d) * (p - a) / (a - c)) + b;

			if((min(b, d) <= inter_ans) && (inter_ans <= max(b, d)) && (min(q, s) <= inter_ans) && (inter_ans <= max(q, s))) {
				if(flag == 0) {
					flag = 1;

					inter1.x = p;

					inter1.y = inter_ans;

					intersect_idx1[0] = index1;
					intersect_idx1[1] = index2;
				}
				else {
					inter2.x = p;

					inter2.y = inter_ans;

					intersect_idx2[0] = index1;
					intersect_idx2[1] = index2;
				}
			}
		}
		else if(q == s) {
			inter_ans = ((q - b) * (a - c) / (b - d)) + a;
#ifdef DEBUG
			printf("###q==s criteria ok###\n");
			printf("inter_ans = %.10f\n", inter_ans);
			printf("\n\n");
#endif

			if((min(a, c) <= inter_ans) && (inter_ans <= max(a, c)) && (min(p, r) <= inter_ans) && (inter_ans <= max(p, r))) {
#ifdef DEBUG
				printf("q==s criteria and inter_ans criteria ok\n\n");
#endif
				if(flag == 0) {
					flag = 1;

					inter1.x = inter_ans;

					inter1.y = q;

					intersect_idx1[0] = index1;
					intersect_idx1[1] = index2;
				}
				else {
					inter2.x = inter_ans;

					inter2.y = q;

					intersect_idx2[0] = index1;
					intersect_idx2[1] = index2;
				}
			}
		}
		else {
			inter_ans = ((a*d*r) - (a*d*p) + (a*p*s) - (c*p*s) - (a*r*q) + (b*c*p) + (c*q*r) - (b*c*r)) / ((b*p) - (b*r) - (d*p) + (d*r) - (a*q) - (c*s) + (a*s) + (c*q));	

			if((min(a, c) <= inter_ans) && (inter_ans <= max(a, c)) && (min(p, r) <= inter_ans) && (inter_ans <= max(p, r))) {
				if(flag == 0) {
					flag = 1;

					inter1.x = inter_ans;

					inter1.y = ((b-d)*(inter_ans - a) / (a-c)) + b;

					intersect_idx1[0] = index1;
					intersect_idx1[1] = index2;
				}
				else {
					inter2.x = inter_ans;

					inter2.y = ((b-d)*(inter_ans - a) / (a-c)) + b;

					intersect_idx2[0] = index1;
					intersect_idx2[1] = index2;
				}
			}
		}
	}


	return 0;
}

double cross(double ax, double ay, double bx, double by) 
{
	return (ax * by - ay * bx);
}

int main()
{
	scanf("%d %d", &N, &M);	

	for(int i = 0; i < N; i++) {
		int tempx, tempy;
		
		scanf("%d %d", &tempx, &tempy);

		DOT input;
			
		input.x = (double)tempx;
		input.y = (double)tempy;

		con1.push_back(input);	
	}	

	for(int i = 0; i < M; i++) {
		int tempx, tempy;
		
		scanf("%d %d", &tempx, &tempy);

		DOT input;
			
		input.x = (double)tempx;
		input.y = (double)tempy;

		con2.push_back(input);	
	}	

	intersect_idx1[0] = -1;
	intersect_idx1[1] = -1;
	intersect_idx2[0] = -1;
	intersect_idx2[1] = -1;

	inter1.x = -10000;
	inter1.x = -10000;
	inter2.y = -10000;
	inter2.y = -10000;

	flag = 0;
	for(int i = 0; i < N; i++) {
		for(int j = 0; j < M; j++) {
			intersect_decision(con1[i], con1[((i + 1) == N) ? 0 : (i + 1)], con2[j], con2[((j + 1) == M)? 0 : (j + 1)], i, j);			
		}
	}
#ifdef DEBUG
	printf("###intersection point check###\n");
	printf("intersect point 1 : %.10f, %.10f\n", inter1.x, inter1.y); 
	printf("intersect point 2 : %.10f, %.10f\n", inter2.x, inter2.y); 
	printf("idx_inter1 -- con1 : %d, con2 : %d\n", intersect_idx1[0], intersect_idx1[1]);
	printf("idx_inter2 -- con1 : %d, con2 : %d\n", intersect_idx2[0], intersect_idx2[1]);
	printf("\n\n");
#endif


	//make overlap dots list (ccw)
	double dir_res;

	dir_res = cross((con1[intersect_idx1[0]].x - con1[(intersect_idx1[0] + 1) == N ? 0 : (intersect_idx1[0] + 1)].x), 
			(con1[intersect_idx1[0]].y - con1[(intersect_idx1[0] + 1) == N ? 0 : (intersect_idx1[0] + 1)].y), 
			(con2[intersect_idx1[1]].x - con2[(intersect_idx1[1] + 1) == M ? 0 : (intersect_idx1[1] + 1)].x),
		       	(con2[intersect_idx1[1]].y - con2[(intersect_idx1[1] + 1) == M ? 0 : (intersect_idx1[1] + 1)].y));	

	overlap.push_back(inter1);

	if(dir_res < 0) {
		int i = (intersect_idx1[0] + 1) == N ? 0 : (intersect_idx1[0] + 1);
		
		while(1) {
			if(i == (((intersect_idx2[0] + 1) == N) ? 0 : (intersect_idx2[0] + 1))) break;

			DOT input;

			input.x = con1[i].x;
			input.y = con1[i].y;

			overlap.push_back(input);

			i++;

			if(i == N) i = 0;
		}	

		overlap.push_back(inter2);

		i = ((intersect_idx2[1] + 1) == M) ? 0 : (intersect_idx2[1] + 1);
#ifdef DEBUG
		printf("i = %d\n", i);
#endif

		while(1) {
			if(i == (((intersect_idx1[1] + 1) == M) ? 0 : (intersect_idx1[1] + 1))) break;

			DOT input;

			input.x = con2[i].x;
			input.y = con2[i].y;

			overlap.push_back(input);

			i++;

			if(i == M) i = 0;
		}
	}
	else if(dir_res > 0) {
		int i = ((intersect_idx1[1] + 1) == M) ? 0 : (intersect_idx1[1] + 1);
		
		while(1) {
			if(i == (((intersect_idx2[1] + 1) == M) ? 0 : (intersect_idx2[1] + 1))) break;

			DOT input;

			input.x = con2[i].x;
			input.y = con2[i].y;

			overlap.push_back(input);

			i++;

			if(i == M) i = 0;
		}	

		overlap.push_back(inter2);

		i = ((intersect_idx2[0] + 1) == N) ? 0 : (intersect_idx2[0] + 1);
#ifdef DEBUG
		printf("i = %d\n", i);
#endif

		while(1) {
			if(i == (((intersect_idx1[0] + 1) == N) ? 0 : (intersect_idx1[0] + 1))) break;

			DOT input;

			input.x = con1[i].x;
			input.y = con1[i].y;

			overlap.push_back(input);

			i++;

			if(i == N) i = 0;
		}
	}

#ifdef DEBUG
	printf("###overlap dots check###\n");
	for(vector<DOT>::iterator it = overlap.begin(); it < overlap.end(); it++) {
		printf("%.10f || %.10f\n", it->x, it->y);
	}
	printf("\n\n");
#endif

	//calculate area of intersect
		

	return 0;
}
