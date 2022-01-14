#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <queue>
#include <vector>
#include <math.h>

using namespace std;

typedef struct __REG {
	int num;
	vector<int> proc;
}REG;

int T;
bool visited[10005];

//idx is the current index of the queue for bfs
int search_bfs(queue<REG> &arr, int tar) 
{
	while(1) {
		if(arr.front().num == tar) {
			for(vector<int>::iterator it = arr.front().proc.begin(); it != arr.front().proc.end(); it++) {
				if(*it == 1) printf("D");
				else if(*it == 2) printf("S");
				else if(*it == 3) printf("L");
				else if(*it == 4) printf("R");
			}
			printf("\n");

			break;
		}	

		REG reg_d, reg_s, reg_l, reg_r;		

		reg_d.num = (arr.front().num * 2) % 10000;
		reg_d.proc = arr.front().proc;
		reg_d.proc.push_back(1);

		reg_s.num = ((arr.front().num - 1) == -1) ? 9999 : (arr.front().num - 1); 
		reg_s.proc = arr.front().proc;
		reg_s.proc.push_back(2);

		reg_l.num = ((arr.front().num % 1000) * 10) + (arr.front().num / 1000); 
		reg_l.proc = arr.front().proc;
		reg_l.proc.push_back(3);

		reg_r.num = (arr.front().num / 10) + ((arr.front().num % 10) * 1000); 
		reg_r.proc = arr.front().proc;
		reg_r.proc.push_back(4);

		arr.pop();

		if(visited[reg_d.num] == false) {
			visited[reg_d.num] = true;
			arr.push(reg_d);
		}

		if(visited[reg_s.num] == false) {
			visited[reg_s.num] = true;
			arr.push(reg_s);
		}

		if(visited[reg_l.num] == false) {
			visited[reg_l.num] = true;
			arr.push(reg_l);
		}

		if(visited[reg_r.num] == false) {
			visited[reg_r.num] = true;
			arr.push(reg_r);
		}
	}

	return 0;

}

int main()
{
	//pair ==> (value, used process to make this value) process 1 = D, 2 = S, 3 = L, 4 = R, 0 = root
	queue<REG> bfs_queue; 

	scanf("%d", &T);

	for(int i = 0; i < T; i++) {
		while(!bfs_queue.empty()) bfs_queue.pop();	

		for(int j = 0; j <= 10000; j++) {
			visited[j] = false;
		}	
		
		int start, target;

		cin >> start >> target;

		REG init;

		init.num = start;
		init.proc.push_back(0);
		visited[start] = true;

		bfs_queue.push(init);

		search_bfs(bfs_queue, target);
	}


	return 0;
}
