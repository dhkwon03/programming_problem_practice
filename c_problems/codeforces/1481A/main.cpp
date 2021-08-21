#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <math.h>

using namespace std;

int t;
string s;

int main()
{
	int u_cnt, d_cnt, l_cnt, r_cnt;
	int px, py;

	cin >> t;

	for(int i = 0; i < t; i++) {
		cin >> px >> py;
		cin >> s;

		u_cnt = 0;	
		d_cnt = 0;	
		r_cnt = 0;	
		l_cnt = 0;	

		for(string::iterator it = s.begin(); it < s.end(); it++) {
			if(*it == 'U') u_cnt++;
			else if(*it == 'D') d_cnt++;
			else if(*it == 'L') l_cnt++;
			else if(*it == 'R') r_cnt++;
		}

		if(px < 0) {
			if(py < 0) {
				if((abs(px) <= l_cnt) && (abs(py) <= d_cnt)) {
					cout << "YES\n";
				}
				else cout << "NO\n";
			}
			else if(py > 0) {
				if((abs(px) <= l_cnt) && (abs(py) <= u_cnt)) {
					cout << "YES\n";
				}
				else cout << "NO\n";
			}
			else {
				if(abs(px) <= l_cnt) {
					cout << "YES\n";
				}
				else cout << "NO\n";
			}
		}
		else if(px > 0) {
			if(py < 0) {
				if((abs(px) <= r_cnt) && (abs(py) <= d_cnt)) {
					cout << "YES\n";
				}
				else cout << "NO\n";
			}
			else if(py > 0) {
				if((abs(px) <= r_cnt) && (abs(py) <= u_cnt)) {
					cout << "YES\n";
				}
				else cout << "NO\n";
			}
			else {
				if(abs(px) <= r_cnt) {
					cout << "YES\n";
				}
				else cout << "NO\n";
			}
		}
		else {
			if(py < 0) {
				if(abs(py) <= d_cnt) cout << "YES\n";
				else cout << "NO\n";
			}
			else if(py > 0) {
				if(abs(py) <= u_cnt) cout << "YES\n";
				else cout << "NO\n";
			}
		}
	}

	return 0;
}
