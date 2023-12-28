#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <math.h>

using namespace std;

int N, r, c;

int solve(int n_st, int n_end, int col_st, int col_end, int row_st, int row_end)
{
    if((n_end - n_st) <= 3) {
        if(c == col_st) {
            if(r == row_st) printf("%d\n", n_st);
            else if(r == row_end) printf("%d\n", (n_st + 2));
        }
        else if(c == col_end) {
            if(r == row_st) printf("%d\n", (n_st + 1));
            else if(r == row_end) printf("%d\n", (n_st + 3));
        }

        return 0;
    }

#ifdef DEBUG
    printf("n_st = %d, n_end = %d, col_st = %d, col_end = %d, row_st = %d, row_end = %d\n", n_st, n_end, col_st, col_end, row_st, row_end);
#endif

    int midrow = (row_st + row_end) / 2;
    int midcol = (col_st + col_end) / 2;

    if(r <= midrow) {
        if(c <= midcol) {
            solve(n_st, (n_st + ((n_end - n_st) / 4)), col_st, midcol, row_st, midrow);
        }
        else {
            solve((n_st + ((n_end - n_st) / 4) + 1), (n_end + n_st) / 2, midcol + 1, col_end, row_st, midrow);
        }
    }
    else {
        if(c <= midcol) {
            solve(((n_st + n_end) / 2) + 1, n_end - ((n_end - n_st) / 4) - 1, col_st, midcol, midrow + 1, row_end);
        }
        else {
            solve(n_end - ((n_end - n_st) / 4), n_end, midcol + 1, col_end, midrow + 1, row_end);
        }
    }

    return 0;
}

int main()
{
    scanf("%d %d %d", &N, &r, &c);

    solve(0, pow(pow(2, N), 2) - 1, 0, pow(2, N) - 1, 0, pow(2, N) - 1);

    return 0;
}
