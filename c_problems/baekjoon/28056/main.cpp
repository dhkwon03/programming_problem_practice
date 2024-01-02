#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

/*
cost[s][e] = min cost for s ~ e

cost k 로 s~e가 모두 merge 된다는 것은
s~e의 모든 branch를 순서대로 b_1, b_2, ..., b_n
그 사이 간격을 순서대로 a_1, a_2, ..., a_(n-1) 이라 하면

for all 1<=i<j<=n, (sigma a_k from k = i to k = j-1) <= (j - i + 1) * K
와 동치임. (K >= ceil((sigma a_k from k = i to k = j-1) / (j - i + 1)) )
define g(i, j) = ceil((sigma a_k from k = i to k = j-1) / (j - i + 1))

cost[s][e] = maximum of g(i, j) when s<=i<j<=e

따라서, cost[s][e-1]과 cost[s+1][e] 중의 최대값은 i = s, j = e일 때를 제외한
모든 경우에 대해 g(i, j) 의 최대값이 된다.
즉, cost[s][e-1]과 cost[s+1][e], g(s, e) 중의 최대값이 곧 cost[s][e]가 됨.

recurrance relation : cost[s][e] = max(cost[s][e-1], cost[s+1][e], g(s,e))
base relation : cost[s][s] = 0, cost[s][s+1] = ceil((s, s+1 branch 사이 간격) / 2)
dynamic programming!

dist array = a_k
*/

int N, Q;
int dist[5005];
int cost[5005][5005];
long long int distsum[5005]; //distsum[i] = sum of dist from dist[1] ~ dist[i]

/*
int solve(int st, int en)
{
    int g_func;

    if(cost[st][en] != -1) return cost[st][en];
    else {
        long long int distsum = 0;
        for(int i = st; i < en; i++) {
            distsum += dist[i];
        }

        //calc g(s,e)
        g_func = (distsum % (long long int)(en - st + 1) == 0) ? (distsum / (long long int)(en-st+1)) : ((distsum / (long long int)(en-st+1)) + 1);

        cost[st][en] = max(solve(st, en - 1), max(solve(st + 1, en), g_func));

        return cost[st][en];
    }
}
*/

int main()
{
    scanf("%d %d", &N, &Q);

    int input_l, input_r;
    int prev_r;

    int sum = 0;
    for(int i = 0; i < N; i++) {
        scanf("%d %d", &input_l, &input_r);

        if(i > 0) {
            dist[i] = input_l - prev_r;

            sum += dist[i];

            distsum[i] = sum;
        }

        prev_r = input_r;
    }

    //initialize based on base relation
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= N; j++) {
            if(i == j) cost[i][j] = 0;
            else if(j == (i + 1)) cost[i][j] = (dist[i] % 2 == 0) ? (dist[i] / 2) : ((dist[i] / 2) + 1);
            else cost[i][j] = -1;
        }
    }

    for(int i = 2; i < N; i++) {
        for(int j = 1; j <= (N - i); j++) {
            int g_func; // g(s, e) which is g(j, j + i)
            g_func = ((distsum[j + i - 1] - distsum[j - 1]) % (long long int)(i + 1) == 0) ? ((distsum[j + i - 1] - distsum[j - 1]) / (long long int)(i+1)) : (((distsum[j + i - 1] - distsum[j - 1]) / (long long int)(i+1)) + 1);
            cost[j][j + i] = max(max(cost[j][j + i - 1], cost[j + 1][j + i]), g_func);
        }
    }

    for(int query = 0; query < Q; query++) {
        int q_s, q_e;

        scanf("%d %d", &q_s, &q_e);

        printf("%d\n", cost[q_s][q_e]);
    }

    return 0;
}
