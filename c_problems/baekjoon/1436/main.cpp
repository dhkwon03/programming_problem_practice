#include <stdio.h>

int N;

/*
7자리 digit에서 6이 연속 3번 나오는 경우의 수를 구해보면 10000을 훨씬 넘는다.
*/

bool checknum(int num) {
    int temp = num;
    
    //0 : idle, 1 : one continuous 6, 2 : two continuous 6, 3 : three continuous 6
    int state = 0;

    while(temp != 0) {
        int cur = temp % 10;
        temp = temp / 10;
        
        if(cur == 6) {
            state++;

            if(state == 3) return true;
        }
        else state = 0;
    }

    return false;
}

int main()
{
    scanf("%d", &N);

    int cur_cnt = 1;
    int num = 666;

    while(1) {
        if(cur_cnt == N) {
            printf("%d\n", num);
            break;
        }

        num++;

        if(checknum(num)) cur_cnt++;
    }

    return 0;
}
