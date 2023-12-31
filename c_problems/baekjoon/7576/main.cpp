#include <stdio.h>
#include <queue>
#include <stdlib.h>
#include <vector>
#include <math.h>

using namespace std;

int M, N;
int arr[1005][1005];
int cnt[1005][1005];
int visited[1005][1005];

queue<pair<int, int>> bfs_qu;

int bfs()
{
    //initialize all start points (where array element is 1)
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            if(arr[i][j] == 1) {
                bfs_qu.push(pair<int, int>(i, j));
                visited[i][j] = 1;
            }
        }
    }

    while(!bfs_qu.empty()) {
        int cur_x, cur_y;

        cur_x = bfs_qu.front().first;
        cur_y = bfs_qu.front().second;
#ifdef DEBUG
        printf("cur_x = %d, cur_y = %d\n", cur_x, cur_y);
        printf("### visited ###\n");
        for(int i = 0; i < N; i++) {
            for(int j = 0; j < M; j++) {
                printf("%d ", visited[i][j]);
            }
            printf("\n");
        }
        printf("\n\n");

        printf("### cnt ###\n");
        for(int i = 0; i < N; i++) {
            for(int j = 0; j < M; j++) {
                printf("%d ", cnt[i][j]);
            }
            printf("\n");
        }
        printf("\n\n");
#endif

        bfs_qu.pop();

        if(((cur_x + 1) < N) && (arr[cur_x + 1][cur_y] == 0) && (visited[cur_x + 1][cur_y] == 0)) {
            cnt[cur_x + 1][cur_y] = cnt[cur_x][cur_y] + 1;
            visited[cur_x + 1][cur_y] = 1;
            bfs_qu.push(pair<int, int>(cur_x + 1, cur_y));
        }
        if(((cur_x - 1) >= 0) && (arr[cur_x - 1][cur_y] == 0) && (visited[cur_x - 1][cur_y] == 0)) {
            cnt[cur_x - 1][cur_y] = cnt[cur_x][cur_y] + 1;
            visited[cur_x - 1][cur_y] = 1;
            bfs_qu.push(pair<int, int>(cur_x - 1, cur_y));
        }
        if(((cur_y + 1) < M) && (arr[cur_x][cur_y + 1] == 0) && (visited[cur_x][cur_y + 1] == 0)) {
            cnt[cur_x][cur_y + 1] = cnt[cur_x][cur_y] + 1;
            visited[cur_x][cur_y + 1] = 1;
            bfs_qu.push(pair<int, int>(cur_x, cur_y + 1));
        }
        if(((cur_y - 1) >= 0) && (arr[cur_x][cur_y - 1] == 0) && (visited[cur_x][cur_y - 1] == 0)) {
            cnt[cur_x][cur_y - 1] = cnt[cur_x][cur_y] + 1;
            visited[cur_x][cur_y - 1] = 1;
            bfs_qu.push(pair<int, int>(cur_x, cur_y - 1));
        }
    }

    return 0;
}

int main()
{
    scanf("%d %d", &M, &N);

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            scanf("%d", &arr[i][j]);

            if(arr[i][j] == -1) cnt[i][j] = -1;
            else cnt[i][j] = 0;

            visited[i][j] = 0;
        }
    }

    bfs();

    int max_cnt = 0;
    bool visit_chk = true;


    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            if(arr[i][j] == 0) {
                if(visited[i][j] == 0) {
                    visit_chk = false;
                    break;
                }

                if(max_cnt < cnt[i][j]) {
                    max_cnt = cnt[i][j];
                }
            }
        }
    }

    if(visit_chk == false) printf("-1\n");
    else printf("%d\n", max_cnt);

    return 0;
}
