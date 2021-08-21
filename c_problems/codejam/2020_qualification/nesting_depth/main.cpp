#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <string>

using namespace std;

int main()
{
	int t;
	string s;
	int arr[105];
	int cur_num;

	cin >> t;

	for(int i = 0; i < t; i++) {
		string ans;
		cin >> s;

		int size = 0;
		for(string::iterator it = s.begin(); it < s.end(); it++) {
			arr[size++] = *it - 48;	
		}


#ifdef DEBUG
		cout << "###array_check###\n";

		for(int j = 0; j < size; j++) {
			cout << arr[j];
		}	

		cout << "\n";
#endif

		for(int j = 0; j < arr[0]; j++) {
			ans.push_back('(');	
		}
		ans.push_back(arr[0] + 48);


		cur_num = arr[0];

		for(int j = 1; j < size; j++) {
			if(arr[j] < arr[j - 1]) {
				for(int k = 0; k < (arr[j - 1] - arr[j]); k++) {
					ans.push_back(')');
				}
				ans.push_back(arr[j] + 48);
				cur_num = arr[j];
			}
			else if(arr[j] == arr[j - 1]) {
				ans.push_back(arr[j] + 48);
			}
			else {
				for(int k = 0; k < (arr[j] - arr[j - 1]); k++) {
					ans.push_back('(');
				}	
				ans.push_back(arr[j] + 48);
				cur_num = arr[j];
			}		
		}

		for(int j = 0; j < cur_num; j++) {
			ans.push_back(')');
		}

		cout << "Case #" << (i + 1) << ": " << ans << "\n";
	}	

	return 0;
}
