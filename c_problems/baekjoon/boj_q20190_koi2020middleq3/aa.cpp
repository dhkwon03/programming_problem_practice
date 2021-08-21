#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <math.h>
#include <algorithm>

using namespace std;

int n;
vector<int> num;
//value of input is the index of num
int input[300005]; 

typedef struct __SEGMENT {
	int seg[1200005], lazy[1200005];

	int update_value(int idx, int start, int end, int left, int right, int value) 
	{
		if((end < left) || (start > right)) return 0;		
		if((start >= left) && (end <= right)) {
			lazy[idx] += value;
			seg[idx] += value;
			return 0;
		}

		seg[2*idx] += lazy[idx];
		seg[2*idx + 1] += lazy[idx];
		lazy[2*idx] += lazy[idx];
		lazy[2*idx + 1] += lazy[idx];

		lazy[idx] = 0;

		int mid = (start + end) / 2;	

		update_value(idx * 2, start, mid, left, right, value);
	      	update_value(idx * 2 + 1, mid + 1, end, left, right, value);	

		seg[idx] = min(seg[2*idx], seg[2*idx + 1]);
			
		return 0;
	}

	int sum_up(int idx, int start, int end, int left, int right)
	{
		if((end < left) || (start > right)) return 99999999 ;		
		if((start >= left) && (end <= right)) {
			return seg[idx];
		}
		
		int mid = (start + end) / 2;

		return min(sum_up(idx * 2, start, mid, left, right), sum_up(idx * 2 + 1, mid + 1, end, left, right))
		       	+ lazy[idx];	

	}		

}SEG;
//segment tree is used for calculating minimum inversion number each case
//for each index, it means how many times that number has an influence on inversion number

typedef struct __FENWICK {
	int arr[300005];

	//+1 for particular idx
	int update(int idx) 
	{
		for(int i = idx; i <= n; i = i + (i & -i)) arr[i]++;
		return 0;
	}	

	//output is the sum of 1 ~ idx
	int sum(int idx) {
		int ans = 0;

		for(int i = idx; i > 0; i = i - (i & -i)) {
			ans += arr[i];
		}	

		return ans;
	}
}FEN;
//fenwick tree is used for calculating initial inversion number

bool compare(int a, int b)
{
	return (a < b);
}

SEG s;
FEN f;


int main()
{
	scanf("%d", &n);

	for(int i = 1; i <= n; i++) {
		scanf("%d", &input[i]); 

		num.push_back(input[i]);
	}

	sort(num.begin(), num.end(), compare);	

	num.erase(unique(num.begin(), num.end()), num.end());

	for(int i = 1; i <= n; i++) {
		input[i] = lower_bound(num.begin(), num.end(), input[i]) - num.begin() + 1;
	}

	long long int init_cnt = 0;
	int num_leng = num.size() + 1; 

	for(int i = n; i >= 1; i--) {
		init_cnt += f.sum(input[i] - 1);

		f.update(input[i]);

		s.update_value(1, 0, num_leng + 1, input[i] + 1, num_leng + 1, 1); 
	}

	for(int i = 1; i <= n; i++) {
		s.update_value(1, 0, num_leng + 1, input[i] + 1, num_leng + 1, -1);

		int cur = s.sum_up(1, 0, num_leng + 1, input[i], input[i]);

		int optimal = s.sum_up(1, 0, num_leng + 1, 0, num_leng + 1);

		printf("%lld ", (init_cnt - cur + optimal));

		s.update_value(1, 0, num_leng + 1, 0, input[i] - 1, 1);
	}

	printf("\n");

	return 0;
}
