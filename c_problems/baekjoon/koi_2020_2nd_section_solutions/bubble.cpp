#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <iostream>
#include <vector>
#include <assert.h>


using namespace std;
int n;
int a[300005];

struct seg{
    int seg[1100005], laz[1100005];
    void upd(int i, int s, int e, int l, int r, int v){
        if(r < s || l > e) return;
        if(l <= s && e <= r){
            laz[i] += v;
            seg[i] += v;
            return;
        }
        int m = (s + e) >> 1;
        seg[2*i] += laz[i]; laz[2*i] += laz[i];
        seg[2*i+1] += laz[i]; laz[2*i+1] += laz[i];
        laz[i] = 0;
        upd(2*i, s, m, l, r, v);
        upd(2*i+1, m+1, e, l, r, v);
        seg[i] = min(seg[2*i], seg[2*i+1]);
    }
    int qry(int i, int s, int e, int l, int r){
        if(r < s || l > e) return INT_MAX;
        if(l <= s && e <= r) return seg[i];
        int m = (s + e) >> 1;
        int ret = min(qry(2*i, s, m, l, r), qry(2*i+1, m+1, e, l, r));
        return ret + laz[i];
    }
} S;

struct BIT{
    int y[300005];
    int sum(int i){
        int s = 0;
        for(;i;i &= i-1) s += y[i];
        return s;
    }
    void add(int i){
        for(;i < 300005; i += i & -i) y[i]++;
    }
} F;

const int mn = 300000;
const int mx = 1000000;
int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);
    cin >> n;
    assert(1 <= n && n <= mn);
    vector<int> c;
    for(int i = 1; i <= n; i++){
        cin >> a[i];
        assert(1 <= a[i] && a[i] <= mx);
        c.push_back(a[i]);
    }
    sort(c.begin(), c.end()); c.erase(unique(c.begin(), c.end()), c.end());
    for(int i = 1; i <= n; i++){
        a[i] = lower_bound(c.begin(), c.end(), a[i]) - c.begin() + 1;
    }
    long long cnt = 0;
    for(int i = n; i >= 1; i--){
        cnt += F.sum(a[i] - 1);
#ifdef DEBUG
	printf("F_sum : %lld\n", F.sum(a[i] - 1));
#endif
        F.add(a[i]);
        S.upd(1, 0, n + 1, a[i] + 1, n + 1, 1);
    }

#ifdef DEBUG
    printf("cnt : %lld\n, size : %d\n", cnt, c.size());
#endif


    long long ans = cnt;
    for(int i = 1; i <= n; i++){
        S.upd(1, 0, n + 1, a[i] + 1, n + 1, -1);
        int val = S.qry(1, 0, n + 1, a[i], a[i]);
        int opt = S.qry(1, 0, n + 1, 0, n + 1);
        cout << cnt - val + opt << ' ';
        S.upd(1, 0, n + 1, 0, a[i] - 1, 1);
    }
    cout << '\n';
}
