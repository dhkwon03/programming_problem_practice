#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <math.h>
#include <vector>

typedef struct __POINT {
	int x;
	int y;
}POINT;

int n;
POINT arr[100005];
int ans;

bool compare(POINT a, POINT b) {
	return (a.x < b.x);
}

bool compare_y(POINT a, POINT b) {
	return (a.y < b.y);
}


int find_closest(int l_idx, int r_idx) {
	if(l_idx == r_idx) return 999999999; 

	int m_idx = (l_idx + r_idx) / 2;
	
	int min_dist;

	min_dist = find_closest(l_idx, m_idx);
	min_dist = std::min(min_dist, find_closest((m_idx + 1), r_idx));

	//check the distance between the points when the one in left side, another one in right side
	std::vector<POINT> to_check;

	int idx_it;
	idx_it = m_idx;
	while(1) {
		if(idx_it < l_idx) break;
		if((arr[m_idx].x - arr[idx_it].x) >= sqrt(min_dist)) break;
		else {
			to_check.push_back(arr[idx_it]);
			idx_it--;
		}
	}

	idx_it = m_idx + 1;
	while(1) {
		if(idx_it > r_idx) break;
		if((arr[idx_it].x - arr[m_idx].x) >= sqrt(min_dist)) break;
		else {
			to_check.push_back(arr[idx_it]);
			idx_it++;
		}
	}

	std::sort(to_check.begin(), to_check.end(), compare_y);


	int to_check_size = to_check.size();

#ifdef DEBUG
	printf("%d\n", to_check_size);
#endif

	if(to_check_size != 0) {
		for(int i = 0; i < to_check_size; i++) {
			for(int j = 1; (i + j) < to_check_size; j++) {
				if(j > 7) break;

				min_dist = std::min(min_dist, (((to_check[i].x - to_check[i+j].x) * (to_check[i].x - to_check[i+j].x)) + ((to_check[i].y - to_check[i+j].y) * (to_check[i].y - to_check[i+j].y))));
			}
		}
	}

	return min_dist;
}

int main()
{
	scanf("%d", &n);

	for(int i = 0; i < n; i++) {
		scanf("%d %d", &arr[i].x, &arr[i].y);
	}

	std::sort(arr, arr + n, compare);

	ans = find_closest(0, (n - 1));

	printf("%d\n", ans);

	return 0;
}
