#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
#include <map>

using namespace std;

struct BUILDING {
	int lx, rx;
	int h;  
};

int n;
BUILDING arr[100005];
map<int,int> x_idx;
vector<int> x_coord;
priority_queue<BUILDING, > pq;

bool compare(BUILDING a, BUILDING b)
{
	return (a.lx < b.lx);
}

int main()
{
	scanf("%d", &n);

	for(int i = 0; i < n; i++) {
		scanf("%d %d %d", &arr[i].lx, &arr[i].h, &arr[i].rx);

		x_idx[arr[i].lx] = 0;			
		x_idx[arr[i].rx] = 0;			
	}	 

	sort(arr, arr+n, compare);

	int cnt = 0;

	//x_idx is sorted automatically by key value(original function) 
	for(map<int,int>::iterator it = x_idx.begin(); it != x_idx.end(); it++) {
		x_idx[it->first] = cnt++;
		x_coord.push_back(it->first);
	}



	int j = 0;
	int cur_height = 0;
	int next_height;
	//cnt = the number of unique x coordinates
	for(int i = 0; i < cnt; i++) {
		while((j < n) && x[arr[j].lx] <= i) {
			pq.push(arr[j]);		
			j++;
		}		

		while(!pq.empty()) {
			if(
		}	
	}	

	return 0;
}
