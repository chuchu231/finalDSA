// the weight graph
// A C++ program for Dijkstra's single source shortest path algorithm.
// The program is for adjacency matrix representation of the graph
/*
#include <limits.h>
#include <stdio.h>

// Number of vertices in the graph
#define V 9

// A utility function to find the vertex with minimum distance value, from
// the set of vertices not yet included in shortest path tree
int minDistance(int dist[], bool sptSet[])
{
	// Initialize min value
	int min = INT_MAX, min_index;

	for (int v = 0; v < V; v++)
		if (sptSet[v] == false && dist[v] <= min)
			min = dist[v], min_index = v;

	return min_index;
}

// A utility function to print the constructed distance array
int printSolution(int dist[], int n)
{
	printf("Vertex Distance from Source\n");
	for (int i = 0; i < V; i++)
		printf("%d \t\t %d\n", i, dist[i]);
}

// Function that implements Dijkstra's single source shortest path algorithm
// for a graph represented using adjacency matrix representation
void dijkstra(int graph[V][V], int src)
{
	int dist[V]; // The output array. dist[i] will hold the shortest
	// distance from src to i

	bool sptSet[V]; // sptSet[i] will be true if vertex i is included in shortest
	// path tree or shortest distance from src to i is finalized

	// Initialize all distances as INFINITE and stpSet[] as false
	for (int i = 0; i < V; i++)
		dist[i] = INT_MAX, sptSet[i] = false;

	// Distance of source vertex from itself is always 0
	dist[src] = 0;

	// Find shortest path for all vertices
	for (int count = 0; count < V - 1; count++) {
		// Pick the minimum distance vertex from the set of vertices not
		// yet processed. u is always equal to src in the first iteration.
		int u = minDistance(dist, sptSet);

		// Mark the picked vertex as processed
		sptSet[u] = true;

		// Update dist value of the adjacent vertices of the picked vertex.
		for (int v = 0; v < V; v++)

			// Update dist[v] only if is not in sptSet, there is an edge from
			// u to v, and total weight of path from src to v through u is
			// smaller than current value of dist[v]
			if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX
				&& dist[u] + graph[u][v] < dist[v])
				dist[v] = dist[u] + graph[u][v];
	}

	// print the constructed distance array
	printSolution(dist, V);
}

// driver program to test above function
int main()
{
	// Let us create the example graph discussed above 
	int graph[V][V] = { { 0, 4, 0, 0, 0, 0, 0, 8, 0 },
						{ 4, 0, 8, 0, 0, 0, 0, 11, 0 },
						{ 0, 8, 0, 7, 0, 4, 0, 0, 2 },
						{ 0, 0, 7, 0, 9, 14, 0, 0, 0 },
						{ 0, 0, 0, 9, 0, 10, 0, 0, 0 },
						{ 0, 0, 4, 14, 10, 0, 2, 0, 0 },
						{ 0, 0, 0, 0, 0, 2, 0, 1, 6 },
						{ 8, 11, 0, 0, 0, 0, 1, 0, 7 },
						{ 0, 0, 2, 0, 0, 0, 6, 7, 0 } };

	dijkstra(graph, 0);

	return 0;
}
*/

/*
#include<iostream>
#include<stdio.h>
using namespace std;
#define INFINITY 9999
#define max 5
void dijkstra(int G[max][max], int n, int startnode);
int main() {
	int G[max][max] = { {0,1,0,3,10},{1,0,5,0,0},{0,5,0,2,1},{3,0,2,0,6},{10,0,1,6,0} };
	int n = 5;
	int u = 0;
	dijkstra(G, n, u);
	return 0;
}
void dijkstra(int G[max][max], int n, int startnode) {
	int cost[max][max], distance[max], pred[max];
	int visited[max], count, mindistance, nextnode, i, j;
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			if (G[i][j] == 0)
				cost[i][j] = INFINITY;
			else
				cost[i][j] = G[i][j];
	for (i = 0; i < n; i++) {
		distance[i] = cost[startnode][i];
		pred[i] = startnode;
		visited[i] = 0;
	}
	distance[startnode] = 0;
	visited[startnode] = 1;
	count = 1;
	while (count < n - 1) {
		mindistance = INFINITY;
		for (i = 0; i < n; i++)
			if (distance[i] < mindistance && !visited[i]) {
				mindistance = distance[i];
				nextnode = i;
			}
		visited[nextnode] = 1;
		for (i = 0; i < n; i++)
			if (!visited[i])
				if (mindistance + cost[nextnode][i] < distance[i]) {
					distance[i] = mindistance + cost[nextnode][i];
					pred[i] = nextnode;
				}
		count++;
	}
	for (i = 0; i < n; i++)
		if (i != startnode) {
			cout << " Distance of node"<<i<<" = "<<distance[i];
				cout << "Path = "<<i;
				j = i;
			do {
				j = pred[j];
				cout << "<-" << j;
			} while (j != startnode);
		}
}*/

#include <iostream>
#include <queue>
#include<vector>
using namespace std;
using ll = long long;
const int maxn = 1000001;
int n, m,s,t;
// s la diem bat dau
vector<pair<int, int>> adj[maxn];

void nhap() {
	cout << "Nhap n, m, s, t: ";
	cin >> n >> m >> s>>t;
	for (int i = 0; i < m; i++) {
		int x, y, w;
		cin >> x >> y >> w;
		adj[x].push_back({ y,w });
		//adj[y].push_back({ x,w });
	}
}

const int INF = 1e9;
int pre[maxn];
void dijkstra(int s, int t) {
	vector<ll>d(n + 1, INF);
	d[s] = 0;
	priority_queue<pair<int, int>, vector<pair<int, int>> , greater<pair<int, int>> > Q;
	Q.push({ 0,s });
	while (!Q.empty()) {
		pair<int, int> top = Q.top();
		Q.pop();
		int u = top.second;
		int kc = top.first;
		if (kc < d[u]) continue;
		for (auto it : adj[u]) {
			int v = it.first;
			int w = it.second;
			if (d[v] > d[u] + w) {
				d[v] = d[u] + w;
				Q.push({ d[v],v });
				pre[v] = u;
			}
		}
	}
	/*for (int i = 0; i <= n; i++) {
		cout << d[i] << " ";
	}*/
	cout << d[t] << endl;
	vector<int> path;
	while (1) {
		path.push_back(t);
		if (t == s) break;
		t = pre[t];
	}
	reverse(begin(path), end(path));
	for (int x : path) {
		cout << x <<" ";
	}
}

int main() {
	nhap();
	dijkstra(s,t);
	return 0;
}
