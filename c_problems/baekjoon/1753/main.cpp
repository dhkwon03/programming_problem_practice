#include <iostream>
#include <algorithm>
#include <math.h>
#include <vector>
#include <queue>

#define MAXVAL 300000000

using namespace std;

typedef struct __WEIGHT {
	int node, wei;
}WEIGHT;

bool operator <(WEIGHT a, WEIGHT b) 
{
	return (a.wei > b.wei);
}

int V, E, K;	
vector<WEIGHT> graph[20005];
//min distance between start vertex and index vertex
int dist[20005];
priority_queue<WEIGHT> order;


int dijkstra()
{
	for(int i = 1; i <= V; i++) {
		if(i == K) dist[i] = 0;
		else dist[i] = MAXVAL;
	}		

	WEIGHT forpush;

	forpush.node = K;
	forpush.wei = 0;	

	order.push(forpush);

	while(!order.empty()) {
		int cur = order.top().node;
		int cur_wei = order.top().wei;

		order.pop();
		
		if(dist[cur] < cur_wei) continue;

		for(int i = 0; i < graph[cur].size(); i++) {
			if ((cur_wei + graph[cur][i].wei) < dist[graph[cur][i].node]) {
				forpush.node = graph[cur][i].node;
				forpush.wei = cur_wei + graph[cur][i].wei;	
				order.push(forpush);

				dist[graph[cur][i].node] = cur_wei + graph[cur][i].wei;
			}
		}		
	}

	return 0;		
}	

int main()
{
	cin >> V >> E;
	cin >> K;

	for(int i = 0; i < E; i++) {
		int input1, input2, input3;

		cin >> input1 >> input2 >> input3;

		WEIGHT graph_input;

		graph_input.node = input2;
		graph_input.wei = input3;

		graph[input1].push_back(graph_input);
	}

	dijkstra();			

	for(int i = 1; i <= V; i++) {
		if(dist[i] == MAXVAL) cout << "INF\n";
		else cout << dist[i] << "\n";
	}

	return 0;
}

