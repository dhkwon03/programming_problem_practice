#include <stdio.h>
#include <algorithm>

int N, M;
long long int arr[100005];

int main()
{
    scanf("%d", &N);

    for(int i = 0; i < N; i++) {
        scanf("%lld", &arr[i]);
    }

    std::sort(arr, arr+N);

    scanf("%d", &M);

    for(int i = 0; i < M; i++) {
        long long int input;
        scanf("%lld", &input);
        long long int high, low, mid;

        int flag = 0;

        high = N - 1;
        low = 0;

        while(low <= high) {
            mid = (high + low) / 2;

            if(arr[mid] > input) high = mid - 1;
            else if(arr[mid] < input) {
                low = mid + 1;
            }
            else if(arr[mid] == input) {
                flag = 1;
                printf("1\n");
                break;
            }
        }

        if(flag == 0) printf("0\n");
    }
    
    return 0;
}
