#include <stdio.h>
#include <vector>
#include <stdlib.h>
#include <iostream>

using namespace std;

vector<vector<int> > arr; 
int k, h;
char method[20];


int main()
{
	scanf("%d", &k);

	for(int i = 0; i < (2*k); i++) {
		scanf(" %c", &method[i]);
	}	

	scanf("%d", &h);

	//initialization
	vector<int> input;

	input.push_back(h);

	arr.push_back(input);

	//scan change method opposite way
	for(int i = 1; i <= (2 * k); i++) {
		char change;

		change = method[(2*k) - i];	
#ifdef DEBUG
		printf("### start : now change method - %c\n\n", change);
#endif

		if(change == 'D') {
			vector<vector<int> > temp;

			for(vector<vector<int> >::iterator it = arr.end() - 1; it >= arr.begin(); it--) {
				vector<int> temp2;

				for(vector<int>::iterator it2 = it->begin(); it2 < it->end(); it2++) {
					if(*it2 == 0) temp2.push_back(2);
					if(*it2 == 1) temp2.push_back(3);
					if(*it2 == 2) temp2.push_back(0);
					if(*it2 == 3) temp2.push_back(1);
				}	
				temp.push_back(temp2);
			}	

			arr.insert(arr.begin(), temp.begin(), temp.end());
		}
		else if(change == 'U') {
			vector<vector<int> > temp;

			for(vector<vector<int> >::iterator it = arr.end() - 1; it >= arr.begin(); it--) {
				vector<int> temp2;

				for(vector<int>::iterator it2 = it->begin(); it2 < it->end(); it2++) {
					if(*it2 == 0) temp2.push_back(2);
					if(*it2 == 1) temp2.push_back(3);
					if(*it2 == 2) temp2.push_back(0);
					if(*it2 == 3) temp2.push_back(1);
				}	
				temp.push_back(temp2);
			}	

			arr.insert(arr.end(), temp.begin(), temp.end());
		}
		else if(change == 'R') {
#ifdef DEBUG
			printf("### process R ###\n");
#endif

			for(vector<vector<int> >::iterator it = arr.begin(); it < arr.end(); it++) {
				vector<int> temp;

				for(vector<int>::iterator it2 = it->end() - 1; it2 >= it->begin(); it2--) {
					if(*it2 == 0) temp.push_back(1);
					if(*it2 == 1) temp.push_back(0);
					if(*it2 == 2) temp.push_back(3);
					if(*it2 == 3) temp.push_back(2);
				}

#ifdef DEBUG
				for(vector<int>::iterator ita = temp.begin(); ita < temp.end(); ita++) {
						printf("%d ", *ita);
				}
				printf("\n");
#endif

				it->insert(it->begin(), temp.begin(), temp.end());
			}	
		}
		else if(change == 'L') {
			for(vector<vector<int> >::iterator it = arr.begin(); it < arr.end(); it++) {
				vector<int> temp;

				for(vector<int>::iterator it2 = it->end() - 1; it2 >= it->begin(); it2--) {
					if(*it2 == 0) temp.push_back(1);
					if(*it2 == 1) temp.push_back(0);
					if(*it2 == 2) temp.push_back(3);
					if(*it2 == 3) temp.push_back(2);
				}

				it->insert(it->end(), temp.begin(), temp.end());
			}	
		}
#ifdef DEBUG
		printf("###for debug### : method %d\n", (2*k) - i); 
		for(vector<vector<int> >::iterator ita = arr.begin(); ita < arr.end(); ita++) {
			for(vector<int>::iterator itb = ita->begin(); itb < ita->end(); itb++) {
				printf("%d ", *itb);
			}	
			printf("\n");
		}
		printf("\n");
#endif
		
	}

	for(vector<vector<int> >::iterator it = arr.begin(); it < arr.end(); it++) {
		for(vector<int>::iterator it2 = it->begin(); it2 < it->end(); it2++) {
			printf("%d ", *it2);
		}	
		printf("\n");
	}

	return 0;
}
