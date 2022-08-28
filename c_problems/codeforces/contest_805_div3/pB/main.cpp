#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

using namespace std;

int main()
{
	int T;
	scanf("%d", &T);

	char word[200005];
	int used[26];

	for(int i = 0; i < T; i++) {
		scanf("%s", word);

		int idx;
		int word_len = int(strlen(word));

		for(int j = 0; j < 26; j++) {
			used[j] = 0;	
		}

		int ans = 0;
		int cnt = 0;

		for(int j = 0; j < word_len; j++) {
			if(used[word[j] - 'a'] == 0) {
				used[word[j] - 'a'] = 1;
				cnt++;
			}

			if(cnt == 4) {
				ans++;
				cnt = 1;
				for(int k = 0; k < 26; k++) {
					used[k] = 0;	
				}
				used[word[j] - 'a'] = 1;
			}
		}

		if(cnt != 0) ans++;

		printf("%d\n", ans);
	}

	return 0;
}
