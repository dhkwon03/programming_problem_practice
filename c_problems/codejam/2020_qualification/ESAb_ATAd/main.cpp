#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>

using namespace std;

int t, b;
// ans[i] = 2 : not filled
int ans[105];
// vector same and diff stores index of left in same pair and different pair 
vector<int> same;
vector<int> diff;
//representing pair of same and diff pair, to confirm operation
//index of left
int same_repre_idx;
int diff_repre_idx;
//num
int same_repre_num;
int diff_repre_num;
int cnt;
int query;

int main()
{
	cin >> t >> b;		

	for(int i = 1; i <= t; i++) {
		fill(ans, ans + (b + 1), 2);
		same.clear();
		diff.clear();
		same_repre_idx = 0;
		diff_repre_idx = 0;
		//scanning variable for index of ans
		//cnt is the left index of scanning pair 
		cnt = 1;
		query = 0;

		while(1) {
			string response1, response2;
			if(cnt == ((b/2) + 1)) {
				break;
			}

			//update ans array
			if((query != 0) && (query % 10 == 0)) {
								

			}

			else {
				cout << cnt << endl;
				cin >> response1;
				if(response1 == 'N') return 0;
				cout << (b - cnt) << endl;
				cin >> response2;
				if(response2 == 'N') return 0;
				query += 2;

				ans[cnt] = response1;
				ans[b - cnt] = response2;

				cnt++;
			}

			if((same_repre_idx == 0) && (response1 == response2)) {
				same_repre_idx = 	
			}
				
		}
		
		for(int j = 1; j <= b; j++) {
			cout << ans[j];
		}
		cout << endl;

		string response;

		cin >> response;

		if(response == 'N') break;
	}

	return 0;
}
