#include <stdio.h>
#include <math.h>
#include <vector>

using namespace std;

typedef struct __NUM {
	int num;
	int cnt;
}NUM;

int main()
{
	int t, n, m, k;
	int a[50005];
	int b[50005];
	vector<NUM> alla;
	vector<NUM> allb;

	scanf("%d", &t);

	for(int i = 0; i < t; i++) {
		alla.clear();
		allb.clear();
		scanf("%d %d", &n, &m);

		for(int j = 0; j < n; j++) {
			scanf("%d", &a[j]);		
		}

		scanf("%d", &k);
		for(int j = 0; j < k; j++) {
			scanf("%d", &b[j]);
		}

		for(int j = 0; j < n; j++) {
			int temp;
			temp = a[j];
			while((temp % m) == 0) {
				temp = temp / m;
			}

			if((alla.size() != 0) && (alla[alla.size() - 1].num == temp)) {
				alla[alla.size() - 1].cnt += a[j] / temp;
			}
			else {
				NUM adding;

				adding.num = temp;
				adding.cnt = a[j] / temp;

				alla.push_back(adding);
			}
		}

		for(int j = 0; j < k; j++) {
			int temp;
			temp = b[j];
			while((temp % m) == 0) {
				temp = temp / m;
			}

			if((allb.size() != 0) && (allb[allb.size() - 1].num == temp)) {
				allb[allb.size() - 1].cnt += b[j] / temp;
			}
			else {
				NUM adding;

				adding.num = temp;
				adding.cnt = b[j] / temp;

				allb.push_back(adding);
			}
		}

		if(alla.size() == allb.size()) {
			int flag = 0;
			for(int j = 0; j < alla.size(); j++) {
				if((alla[j].num != allb[j].num) || (alla[j].cnt != allb[j].cnt)) {
					flag = 1;
					break;
				}
			}

			if(flag == 1) printf("No\n");
			else printf("Yes\n");
		}
		else {
			printf("No\n");	
		}
	}

	return 0;
}
