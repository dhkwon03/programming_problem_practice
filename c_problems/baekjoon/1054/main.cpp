#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <algorithm>
#include <string.h>

using namespace std;

int N;
char words[15][15];
int word_len[15];
long long int palindrome[8200][2][13][13];
int used[15];

int main()
{
	scanf("%d", &N);

	for(int i = 0; i < N; i++) {
		scanf("%s", words[i]);

		word_len[i] = strlen(words[i]);			
	}

	check_word_if_palindrome();

	for(int i = 0; i < N; i++) {
		solve(0, i, 0, NULL);	
	}

	return 0;
}

