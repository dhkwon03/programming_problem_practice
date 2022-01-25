#include <iostream>

using namespace std;

int N;
int cur;

int main()
{
	cin >> N;

	cur = 1;
	int side; //side = 0 : left, 1 : right 
	int side_loc; //location at that side
	for(int i = 0; i < N; i++) {
		int input;
		int input_cnt = 0; 

		if(cur >= 14) {
			side = 1;
			side_loc = cur - 13;	
		}
		else {
			side = 0;
			side_loc = cur;
		}

		int now_deck;
		now_deck = 0;
		input_cnt = 0;
		do {
			cin >> input; 
			input_cnt++;

			if(side_loc == 0) continue;
			else {
				if(input_cnt % 2 == 1) {
					if(side == 1) {
						if(input >= side_loc) {
							cur = now_deck + side_loc;
							side_loc = 0;
						}
						else {
							side_loc -= input;	
							now_deck += input;
						}
					}
					else {
						now_deck += input;
					}				
				}
				else {
					if(side == 0) {
						if(input >= side_loc) {
							cur = now_deck + side_loc;
							side_loc = 0;
						}
						else {
							side_loc -= input;	
							now_deck += input;
						}
					}
					else {
						now_deck += input;
					}				
				}
			}

		} while(getc(stdin) == ' ');		
	}	

	cout << cur << endl;

	return 0;
}
