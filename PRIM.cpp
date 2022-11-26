// PRIM ma tran ke
/*
#include <iostream>
using namespace std;

// Number of vertices in the graph
#define V 5

// A utility function to find the vertex with
// minimum key value, from the set of vertices
// not yet included in MST
int minKey(int key[], bool mstSet[])
{
	// Initialize min value
	int min = INT_MAX, min_index;

	for (int v = 0; v < V; v++)
		if (mstSet[v] == false && key[v] < min)
			min = key[v], min_index = v;

	return min_index;
}

// A utility function to print the
// constructed MST stored in parent[]
void printMST(int parent[], int graph[V][V])
{
	cout << "Edge \tWeight\n";
	for (int i = 1; i < V; i++)
		cout << parent[i] << " - " << i << " \t"
		<< graph[i][parent[i]] << " \n";
}

// Function to construct and print MST for
// a graph represented using adjacency
// matrix representation
void primMST(int graph[V][V])
{
	// Array to store constructed MST
	int parent[V];

	// Key values used to pick minimum weight edge in cut
	int key[V];

	// To represent set of vertices included in MST
	bool mstSet[V];

	// Initialize all keys as INFINITE
	for (int i = 0; i < V; i++)
		key[i] = INT_MAX, mstSet[i] = false;

	// Always include first 1st vertex in MST.
	// Make key 0 so that this vertex is picked as first
	// vertex.
	key[0] = 0;
	parent[0] = -1; // First node is always root of MST

	// The MST will have V vertices
	for (int count = 0; count < V - 1; count++) {
		// Pick the minimum key vertex from the
		// set of vertices not yet included in MST
		int u = minKey(key, mstSet);

		// Add the picked vertex to the MST Set
		mstSet[u] = true;

		// Update key value and parent index of
		// the adjacent vertices of the picked vertex.
		// Consider only those vertices which are not
		// yet included in MST
		for (int v = 0; v < V; v++)

			// graph[u][v] is non zero only for adjacent
			// vertices of m mstSet[v] is false for vertices
			// not yet included in MST Update the key only
			// if graph[u][v] is smaller than key[v]
			if (graph[u][v] && mstSet[v] == false
				&& graph[u][v] < key[v])
				parent[v] = u, key[v] = graph[u][v];
	}

	// print the constructed MST
	printMST(parent, graph);
}

// Driver's code
int main()
{
	/* Let us create the following graph
		2 3
	(0)--(1)--(2)
	| / \ |
	6| 8/ \5 |7
	| / \ |
	(3)-------(4)
			9	 
	int graph[V][V] = { { 0, 2, 0, 6, 0 },
						{ 2, 0, 3, 8, 5 },
						{ 0, 3, 0, 0, 7 },
						{ 6, 8, 0, 0, 9 },
						{ 0, 5, 7, 9, 0 } };

	// Print the solution
	primMST(graph);

	return 0;
}

*/

// PRIM danh sach ke using priority_queue

#include <iostream>
#include<queue>
using namespace std;


const int maxn = 1001;

struct canh {
	int x, y, w;
};


int n, m; //n : so luong dinh, m so luong canh
vector<pair<int, int>> adj[maxn];
bool used[maxn]; // used[i] = true : i thuoc tap V(MST), used[i] = false : i thuoc tap v
int parent[maxn], d[maxn];

void nhap() {
	cout << "Enter V and E: ";
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int x, y, w; cin >> x >> y >> w;
		adj[x].push_back({ y, w });
		adj[y].push_back({ x, w });
	}
	memset(used, false, sizeof(used));
	for (int i = 1; i <= n; i++) d[i] = INT_MAX;
}


void prim(int u) {
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> Q;
	vector<canh> MST;
	int res = 0;
	Q.push({ 0, u });
	while (!Q.empty()) {
		pair<int, int> top = Q.top(); Q.pop();
		int dinh = top.second, trongso = top.first;

		if (used[dinh]) continue;
		res += trongso;
		used[dinh] = true;
		if (u != dinh) {
			MST.push_back({ dinh, parent[dinh], trongso });
		}
		//duyet tat ca cac dinh ke 
		for (auto it : adj[dinh]) {
			int y = it.first, w = it.second;
			if (!used[y] && w < d[y]) {
				Q.push({ w, y });
				d[y] = w;
				parent[y] = dinh;
			}
		}
	}
	cout << res << endl;
	for (auto it : MST) {
		cout << it.x << " " << it.y << " " << it.w << endl;
	}
}

int main() {
	nhap();
	prim(0);
}

// PRIM danh sach ke 
/*
#include <iostream>
#include<queue>
using namespace std;

const int maxn = 1001;

struct canh {
	int x, y, w;
};

int n, m; //n : so luong dinh, m so luong canh
vector<pair<int, int>> adj[maxn];
bool used[maxn]; // used[i] = true : i thuoc tap V(MST), used[i] = false : i thuoc tap v

void nhap() {
	cout << "Enter V and E: ";
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int x, y, w; cin >> x >> y >> w;
		adj[x].push_back({ y, w });
		adj[y].push_back({ x, w });
	}
	memset(used, false, sizeof(used));
}

void prim(int u) {
	vector<canh> MST; // cay khung
	int d = 0; // chieu dai cay khung
	used[u] = true; // dua dinh u vao tap V(MST)
	while (MST.size() < n - 1) {
		//e = (x, y) : Cạnh ngắn nhất có x thuộc V và y thuộc V(MST)
		int min_w = INT_MAX;
		int X, Y; // luu 2 dinh cua canh e
		for (int i = 1; i <= n; i++) {
			//neu dinh i thuoc tap V(MST)
			if (used[i]) {
				//duyet danh sach ke cua dinh i
				for (pair<int, int> it : adj[i]) {
					int j = it.first, trongso = it.second;
					if (!used[j] && trongso < min_w) {
						min_w = trongso;
						X = j; Y = i;
					}
				}
			}
		}
		MST.push_back({ X, Y, min_w });
		d += min_w;
		used[X] = true; // cho dinh X vao V(MST), loai X khoi tap V
	}
	cout << d << endl;
	for (canh e : MST) {
		cout << e.x << " " << e.y << " " << e.w << endl;
	}
}

int main() {
	nhap();
	prim(0);
} */
