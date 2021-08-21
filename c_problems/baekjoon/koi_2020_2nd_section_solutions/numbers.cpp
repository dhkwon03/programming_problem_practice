#include<iostream>
using namespace std;
#include<algorithm>
int n,k,a[5010],out;
int main()
{
	int i;
	cin>>n>>k;
	for(i=1;i<=n;++i)cin>>a[i];
	sort(&a[1],&a[n+1]);
	for(i=n;i>n-k;--i)out=out+a[i];
	out=out-k*(k-1)/2;
	cout<<out;
	return 0;
}