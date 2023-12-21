#include <stdio.h>

int N, K;
int cur_len[10005];

int lan_cnt(int part_len)
{
    int sum = 0;

    for(int i = 0; i < K; i++) {
        sum += cur_len[i] / part_len;
    }

    return sum;
}

int main()
{


    scanf("%d %d", &K, &N);

    int maxlen = 0;

    for(int i = 0; i < K; i++) {
        scanf("%d", &cur_len[i]);

        if(cur_len[i] > maxlen) maxlen = cur_len[i];
    }

    long long int high, low, mid;

    low = 1;
    high = maxlen;

    int ans;

    while(low <= high) {
        mid = (high + low) / 2;

        if(lan_cnt(mid) < N) high = mid - 1;
        else {
            low = mid + 1;
        }
    }

    printf("%lld\n", high);

    return 0;
}
