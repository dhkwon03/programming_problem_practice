#include <iostream>
#include <cstdio>

using namespace std;

int main()
{
	int ans;
	int flag;
	char input;

	ans = 0;
	flag = 1;
	while((input = getchar()) != EOF) {
		if((flag == 1) && (input != ' ') && (input != EOF) && (input != '\n') && (input != '\0')) {
			ans++;
#ifdef DEBUG
			if((input == ' ') || (input == EOF)) cout << "#";
			else cout << input;
#endif
			flag = 0;
		}
		else if((flag == 0) && (input == ' ')) flag = 1;
	}

	cout << ans << endl;

	return 0;
}
