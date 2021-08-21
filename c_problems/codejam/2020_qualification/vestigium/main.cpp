#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <algorithm>

using namespace std;

int main()
{
	int t;
	int n;
	int arr[105][105];
	bool check[105];
	int trace; 
	int row, col;

	cin >> t;

	for(int i = 0; i < t; i++) {
		cin >> n;

		for(int j = 0; j < n; j++) {
			for(int k = 0; k < n; k++) {
				cin >> arr[j][k];
			}
		}

		trace = 0;
		for(int j = 0; j < n; j++) {
			trace += arr[j][j];
		}

		row = 0;
		col = 0;
		for(int j = 0; j < n; j++) {
			fill(check, check + (n + 1), false);
			for(int k = 0; k < n; k++) {
				if(check[arr[j][k]] == true) {
					row++;			
					break;
				}
				else check[arr[j][k]] = true;
			}
		}

		for(int j = 0; j < n; j++) {
			fill(check, check + (n + 1), false);
			for(int k = 0; k < n; k++) {
				if(check[arr[k][j]] == true) {
					col++;			
					break;
				}
				else check[arr[k][j]] = true;
			}
		}

		cout << "Case #" << (i + 1) << ": " << trace << " " << row << " " << col << "\n";
	}	

	return 0;
}
