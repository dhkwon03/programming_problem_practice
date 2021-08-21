#include <stdio.h>
#include <vector>
#include <algorithm>
#include <stdlib.h>

using namespace std;

int N;

vector<int> road[300005];
//the number of child of each nodes
long long int child_num[300005] = {0, };
int visited[300005] = {0, };
long long int ans;

/*
int layer_assign(int num, int cnt)
{
	layer[num] = cnt;

	for(vector<int>::iterator it = road[num].begin(); it < road[num].end(); it++) {
		if(visited[*it] == 0) {
			visited[*it] = 1;
			layer_assign(*it, (cnt+1));	
		}
	}

	return 0;
}
*/

/*
int direct_path_min_layer(int start_node, int end_node, int cur_node)
{
	if(cur_node == end_node) {
		return 1;
	}	

	for(vector<int>::iterator it = road[cur_node].begin(); it < road[cur_node].end(); it++) {
		if(visited[*it] == 0) {
			visited[*it] = 1;
			if(direct_path_min_layer(start_node, end_node, *it) == 1) {
				if(min_layer_num > layer[cur_node]) min_layer_num = layer[cur_node];	

				return 1;
			}	
		}
	}

	return 0;
}
*/

int cnt_child_node_num(int cur_node)
{
	long long int temp_cnt;

	temp_cnt = 0;
	for(vector<int>::iterator it = road[cur_node].begin(); it < road[cur_node].end(); it++) {
		if(visited[*it] == 0) {
			visited[*it] = 1;
			cnt_child_node_num(*it);
			temp_cnt += child_num[*it];	
		}
	}

	child_num[cur_node] = temp_cnt + 1;

	return 0;
}

int main()
{
	scanf("%d", &N);

	for(int i = 0; i < (N - 1); i++) {
		int na, nb;

		scanf("%d %d", &na, &nb);

		road[na].push_back(nb);
		road[nb].push_back(na);			
	}	

	ans = 0;


	visited[1] = 1;
	cnt_child_node_num(1);		

#ifdef DEBUG
	printf("### child node number check ###\n");
	for(int i = 1; i <= N; i++) {
		printf("child node of %d : %d\n", i, child_num[i]);	
	}
#endif

	//for each edge which connect the node and parent of that node
	//it is counted when two child node or grand child node path exist or one child or grand child node and outer node
	//path exists
	
	for(int i = 2; i <= N; i++) {
		ans += child_num[i] * (N - child_num[i]) + child_num[i] * (child_num[i] - 1) / 2;
	}		
	
	
	//visited[1] = 1;
	/*
	//memo the distance of each nodes from root
	layer_assign(1, 0);		
	*/

	/*
	for(int i = 1; i < N; i++) {
		for(int j = (i + 1); j <= N; j++) {
			min_layer_num = layer[j];
			//find direct path betwenn two nodes and find minimum layer number on that path
			fill(visited, visited + (N+1), 0);
			visited[i] = 1;
			direct_path_min_layer(i, j, i);	

			//A to B diversity = A layer + B layer - (minimum layer number on that path)
			ans += (layer[i] + layer[j] - min_layer_num);
		}
	}
	*/

	printf("%lld\n", ans);
	

	return 0;
	
}
