#include <stdio.h>
#include <utility>
#include <vector>
#include <math.h>
#include <algorithm>
#include <stdlib.h>
#include <string.h>

using namespace std;

int T;
char word[200005];
int P;
int letters[26];
int word_len;
int total;

int main()
{
	scanf("%d", &T);

	for(int i = 0; i < T; i++) {
		scanf("%s", word);
		scanf("%d", &P);		

		word_len = int(strlen(word));		

		for(int j = 0; j < 26; j++) letters[j] = 0;

		total = 0;
		for(int j = 0; j < word_len; j++) {
			letters[word[j] - 'a']++;			
			total += word[j] - 'a' + 1;
		}

		for(int j = 25; j >= 0; j--) {
			if(letters[j] > 0) {
				while((letters[j] > 0) && (total > P)) {
					letters[j]--;
					total -= (j + 1);
				}
			}

			if(total <= P) break;
		}

		for(int j = 0; j < word_len; j++) {
			if(letters[word[j] - 'a'] > 0) {
				printf("%c", word[j]);
				letters[word[j] - 'a']--;
			}
		}
		printf("\n");
	}

	return 0;
}
