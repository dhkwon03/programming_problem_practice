#include <iostream>

using namespace std;

int N, M;
long long int ans;
int bridge[1005][1005];
long long int cache[1005][1005];


int main()
{
	cin >> N >> M;

	for(int i = 0; i < N; i++) {
		for(int j = 0; j < M; j++) {
			cin >> bridge[i][j];	

			cache[i][j] = 0;
		}
	}	
	
	ans = 0;

	for(int i = 0; i < M; i++) {
		if(bridge[0][i] == 1) cache[0][i]++;
	}

	for(int i = 1; i < N; i++) {
		for(int j = 0; j < M; j++) {
			if(bridge[i][j] == 0) continue;
			else {
				if(j == 0) {
					cache[i][j] = cache[i - 1][j] + cache[i - 1][j + 1];
				}	
				else if(j == (M - 1)) {
					cache[i][j] = cache[i - 1][j] + cache[i - 1][j - 1];
				}	
				else {
					cache[i][j] = cache[i - 1][j] + cache[i - 1][j - 1] + cache[i - 1][j + 1];
				}	

				if(cache[i][j] >= 1000000007) {
					cache[i][j] = cache[i][j] % 1000000007;
				}
			}
		}
	}

	for(int i = 0; i < M; i++) {
		ans += cache[N - 1][i];	
	}

	ans = ans % 1000000007;

	cout << ans << endl;

	return 0;
}
