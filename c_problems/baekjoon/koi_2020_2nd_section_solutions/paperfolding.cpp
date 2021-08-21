#include <bits/stdc++.h>
using namespace std;
const int MN = 2005;

char A[30];
int ans[MN][MN];

int main()
{
    ios_base::sync_with_stdio(0),cin.tie(0);

    int K;
    cin >> K;

    for(int i=0; i<2*K; i++) cin >> A[i];
	cin >> ans[0][0];

	int X=1,Y=1;

	for(int i=2*K-1; i>=0; i--){
		if(A[i]=='U'){
			for(int i=0; i<X; i++){
				for(int j=0; j<Y; j++){
					ans[i][j+Y] = ans[i][j];
				}
			}
			for(int i=0; i<X; i++){
				for(int j=0; j<Y; j++){
					ans[i][j] = ans[i][2*Y-1-j]^2;
				}
			}
			Y<<=1;
		}
		else if(A[i]=='D'){
			for(int i=0; i<X; i++){
				for(int j=0; j<Y; j++){
					ans[i][2*Y-1-j] = ans[i][j]^2;
				}
			}
			Y<<=1;			
		}
		else if(A[i]=='L'){
			for(int i=0; i<X; i++){
				for(int j=0; j<Y; j++){
					ans[2*X-1-i][j] = ans[i][j]^1;
				}
			}
			X<<=1;					
		}
		else if(A[i]=='R'){
			for(int i=0; i<X; i++){
				for(int j=0; j<Y; j++){
					ans[i+X][j] = ans[i][j];
				}
			}
			for(int i=0; i<X; i++){
				for(int j=0; j<Y; j++){
					ans[i][j] = ans[2*X-1-i][j]^1;
				}
			}
			X<<=1;				
		}
	}

	for(int j=Y-1; j>=0; j--){
		for(int i=0; i<X; i++){
			cout << ans[i][j];
			cout << (i == X-1 ? "\n" : " ");
		}
	}
}