#include <stdio.h>
#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

int N, M;
vector<int> graph[300005];
vector<int> tree[300005];
int depth[300005];
//cbe : completely included back edge, ibe : included back edge, pbe : parent connected back edge
int cbe[300005], ibe[300005], pbe[300005];

int dfs_search(int parent, int cur)
{
	for(int i = 0; i < graph[cur].size(); i++) {
		int next = graph[cur][i];

		if(next == parent) continue;
		else if(depth[next] == 0) {
			//tree edge
			tree[cur].push_back(next);
			depth[next] = depth[cur] + 1;	
			
			int temp = cbe[cur];

			dfs_search(cur, next);

			pbe[next] = cbe[cur] - temp;
			cbe[cur] += cbe[next];
			ibe[cur] += ibe[next];
		}
		else if(depth[next] < depth[cur]) {
			//back edge	
			ibe[cur]++;	
			cbe[next]++;
		}
	}	

	return 0;	
}

int main()
{
	cin >> N >> M;	

	for(int i = 0; i <= N; i++) {
		depth[i] = 0;
		cbe[i] = 0;
		ibe[i] = 0;
		pbe[i] = 0;
	}

	for(int i = 0; i < M; i++) {
		int input1, input2;

		cin >> input1 >> input2;

		graph[input1].push_back(input2);		
		graph[input2].push_back(input1);		
	}

	depth[1] = 1;		

	dfs_search(0, 1);

	long long int ans = 0;

	for(int vertex = 1; vertex <= N; vertex++) {
		int flag = 0;
		for(int j = 0; j < tree[vertex].size(); j++) {
			int child = tree[vertex][j];

			if(cbe[child] != 0) {
				//back edge inside the sub-tree whose root is child
				flag = 1;
				break;
			}
			else if((ibe[child] - pbe[child]) >= 2) {
				//2 or more back edge between sub-tree (whose root is child) and vertex's ancestor
				flag = 1;
				break;
			}
		}

		if(flag == 1) {
			continue;	
		}
		else if((M - (N - 1) - ibe[vertex]) != 0) {
			//Without sub-tree whose root is vertex, there is back edge else where
			//(N - 1) is the number of tree edges
			//ibe[vertex] : the number of all back edges related to sub-tree whose root is vertex
			continue;
		}

		ans += vertex;	
	}

	cout << ans << endl;
	
	return 0;	
}
