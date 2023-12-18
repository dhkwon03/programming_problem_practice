#include <stdio.h>

/*
1~N/2 까지 root로 해서 각각 root를 x라 하면 depth 2에는 x+1, x+2, ... , x + N/2 연결
x + N/2 에 나머지 node depth 3으로 연결

왜 위의 방법이 명확히 해를 구성하는가를 각 node에 연결되어 있는 edge가 어떻게 각 그래프에 포함되는지 살펴보면...

1~N/2의 범위에 있는 node는 N/2개 edge는 자신이 root인 그래프에서, 나머지는 1~N/2 중 root인 그래프들에서 1개씩 소모
(N/2 + 1) ~ N 의 범위에 있는 node는 1개 그래프에서 2개 edge 소모, 나머지 N/2 - 1 개 graph에서 1개씩 edge 소모

N이 홀수일 때는 몇 개 edge가 2개 이상의 graph에 포함되기는 하나 비슷한 원리로 성립
*/

int main()
{
    int N;
    int K;

    scanf("%d", &N);

    if(N % 2 == 0) {
        printf("%d\n", N / 2);
        K = N/2;
    }
    else {
        printf("%d\n", (N / 2) + 1);
        K = (N/2) + 1;
    }

    for(int i = 1; i <= K; i++) {
        for(int j = 1; j <= (N / 2); j++) {
            printf("%d %d\n", i, (i + j));
        }
        for(int j = 1; j < i; j++) {
            if(j != (i + (N / 2))) {
                printf("%d %d\n", (i + (N / 2)), j);
            }
        }
        for(int j = (i + (N / 2) + 1); j <= N; j++) {
            printf("%d %d\n", (i + (N / 2)), j);
        }
    }

    return 0;
}
