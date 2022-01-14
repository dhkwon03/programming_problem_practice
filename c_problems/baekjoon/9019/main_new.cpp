#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <queue>
#include <vector>
#include <math.h>

using namespace std;

typedef struct __REG {
	bool check; 
	int from; //from what number
	int oper; //operation
}REG;

int T;
REG visited[10005];
queue<int> arr;

//idx is the current index of the queue for bfs
int search_bfs(int tar) 
{
	while(1) {
		if(arr.front() == tar) {
			vector<int> ans;

			int backtrack_n = arr.front();
			while(1) {
				if(visited[backtrack_n].from == -1) break;

				ans.push_back(visited[backtrack_n].oper);

				backtrack_n = visited[backtrack_n].from;
			}	

			vector<int>::iterator it;
			for(vector<int>::iterator it = (ans.end() - 1); it != (ans.begin() - 1); it--) {
				if(*it == 1) printf("D");
				else if(*it == 2) printf("S");
				else if(*it == 3) printf("L");
				else if(*it == 4) printf("R");
			}
			printf("\n");

			break;
		}	

		int reg_d, reg_s, reg_l, reg_r;		

		reg_d = (arr.front() * 2) % 10000;
		reg_s = ((arr.front() - 1) == -1) ? 9999 : (arr.front() - 1); 
		reg_l = ((arr.front() % 1000) * 10) + (arr.front() / 1000); 
		reg_r = (arr.front() / 10) + ((arr.front() % 10) * 1000); 

		if(visited[reg_d].check == false) {
			visited[reg_d].check = true;
			visited[reg_d].from = arr.front();
			visited[reg_d].oper = 1;
			arr.push(reg_d);
		}

		if(visited[reg_s].check == false) {
			visited[reg_s].check = true;
			visited[reg_s].from = arr.front();
			visited[reg_s].oper = 2;
			arr.push(reg_s);
		}

		if(visited[reg_l].check == false) {
			visited[reg_l].check = true;
			visited[reg_l].from = arr.front();
			visited[reg_l].oper = 3;
			arr.push(reg_l);
		}

		if(visited[reg_r].check == false) {
			visited[reg_r].check = true;
			visited[reg_r].from = arr.front();
			visited[reg_r].oper = 4;
			arr.push(reg_r);
		}

		arr.pop();
	}

	return 0;

}

int main()
{
	//operation 1 = D, 2 = S, 3 = L, 4 = R, 0 = root

	scanf("%d", &T);

	for(int i = 0; i < T; i++) {
		while(!arr.empty()) arr.pop();	

		for(int j = 0; j <= 10000; j++) {
			visited[j].check = false;
			//it doesn't matter to initialize from or oper. Because we only need to track start -> target path, other values have no influnece on that path. 
		}	
		
		int start, target;

		cin >> start >> target;

		visited[start].check = true;
		visited[start].from = -1;
		visited[start].oper = 0;

		arr.push(start);

		search_bfs(target);
	}


	return 0;
}
