#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

/*
각 노드마다 자신이 ancestor가 되는 노드들의 (즉, 해당 노드의 자손 및 손자들) 개수를 파악 (i 노드에 대해 n_i 라 정의)
--> n_i 기준 오름차순으로 정렬
정렬한 sequence에서 n_i를 누적시켜 가면서 출력
어떤 node i가 있고 그 node의 ancestor는 j라 하면 항상 n_j > n_i 이고
ancestor를 먼저 검은색 칠하고 이후에 그 밑 자손을 검은색 칠하면 개수가 +2 가 되므로 non-optimal
따라서, 위의 방법이 optimal
*/

int N;
int ancnt[200005]; //ancestor's count (n_i)
vector<int> graph[200005];

int dfs_cnt(int cur)
{
    for(int i = 0; i < graph[cur].size(); i++) {
        ancnt[cur] += dfs_cnt(graph[cur][i]);
    }

    return ancnt[cur] + 1;
}

int main()
{
    scanf("%d", &N);

    for(int i = 1; i <= N; i++) {
        ancnt[i] = 0;
    }

    for(int i = 1; i < N; i++) {
        int i_parent;
        scanf("%d", &i_parent);

        graph[i_parent].push_back(i + 1);
    }

    ancnt[1] = (dfs_cnt(1) - 1);

    sort(ancnt + 1, ancnt + (N + 1));

    printf("0");

    long long int sum = 0;

    for(int i = 1; i <= N; i++) {
        sum += ancnt[i];

        printf(" %lld", sum);
    }

    printf("\n");

    return 0;
}
