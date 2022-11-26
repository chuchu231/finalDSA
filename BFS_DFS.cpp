//#include <iostream>
//using namespace std;
//struct Graph {
//	int V;
//	int E;
//	int** Adj;
//};

// weight graph
/* 
#include <iostream>
using namespace std;
// stores adjacency list items
struct adjNode {
    int val, cost;
    adjNode* next;
};
// structure to store edges
struct graphEdge {
    int start_ver, end_ver, weight;
};
class DiaGraph {
    // insert new nodes into adjacency list from given graph
    adjNode* getAdjListNode(int value, int weight, adjNode* head) {
        adjNode* newNode = new adjNode;
        newNode->val = value;
        newNode->cost = weight;

        newNode->next = head;   // point new node to current head
        return newNode;
    }
    int N;  // number of nodes in the graph
public:
    adjNode** head;                //adjacency list as array of pointers
    // Constructor
    DiaGraph(graphEdge edges[], int n, int N) {
        // allocate new node
        head = new adjNode * [N]();
        this->N = N;
        // initialize head pointer for all vertices
        for (int i = 0; i < N; ++i)
            head[i] = nullptr;
        // construct directed graph by adding edges to it
        for (unsigned i = 0; i < n; i++) {
            int start_ver = edges[i].start_ver;
            int end_ver = edges[i].end_ver;
            int weight = edges[i].weight;
            // insert in the beginning
            adjNode* newNode = getAdjListNode(end_ver, weight, head[start_ver]);

            // point head pointer to new node
            head[start_ver] = newNode;
        }
    }
    // Destructor
    ~DiaGraph() {
        for (int i = 0; i < N; i++)
            delete[] head[i];
        delete[] head;
    }
};
// print all adjacent vertices of given vertex
/*void display_AdjList(adjNode* ptr, int i)
{
    while (ptr != nullptr) {
        cout << "(" << i << ", " << ptr->val
            << ", " << ptr->cost << ") ";
        ptr = ptr->next;
    }
    cout << endl;
}
// graph implementation
//int main()
//{
//    // graph edges array.
//    graphEdge edges[] = {
//        // (x, y, w) -> edge from x to y with weight w
//        {0,1,2},{0,2,4},{1,4,3},{2,3,2},{3,1,4},{4,3,3}
//    };
//    int N = 6;      // Number of vertices in the graph
//    // calculate number of edges
//    int n = sizeof(edges) / sizeof(edges[0]);
//    // construct graph
//    DiaGraph diagraph(edges, n, N);
//    // print adjacency list representation of graph
//    cout << "Graph adjacency list " << endl << "(start_vertex, end_vertex, weight):" << endl;
//    for (int i = 0; i < N; i++)
//    {
//        // display adjacent vertices of vertex i
//        display_AdjList(diagraph.head[i], i);
//    }
//    return 0;
//} */


#include<iostream>
#include <vector>
#include <queue>
using namespace std;
int visited[1000] = { 0 };
int d[1000], p[1000];
vector <int> G[1000];
void bfs(queue<int> q);

void dfs(int k) {
    if (!visited[k]) {
        visited[k] = 1;
        for (int i = 0; i < G[k].size(); i++) {
            if (!visited[G[k][i]]) {
                dfs(G[k][i]);
            }
        }
    }
}

int main() {
    int n; // V
    cout << "Enter the number of V: ";
    cin >> n;
    int edges;
    cout << "Enter the number of E: ";
    cin >> edges;
    while (n <= 0 || edges <= 0) {
        cout << "Enter the number of V: ";
        cin >> n;
        
        cout << "Enter the number of E: ";
        cin >> edges;
    }
    while (edges--) {
        int x, y;
        cin >> x >> y;
        G[x].push_back(y);
        G[y].push_back(x);
    }
    // How can i go from a to b?
    int a, b;
    cout << "Enter a and b: ";
    cin >> a >> b;
    dfs(a);
    if (visited[b] == 1) cout << "YES\n";
    else cout << "NO\n";

    for (int i = 0; i <= n; i++) {
        cout << i <<":" << visited[i] << " ";
    }

   /* int s = 0;
    visited[s] = 1;
    d[s] = 0;
    p[s] = -1;*/
   // queue<int> q;
   // q.push(s);
   ///* while (!q.empty()) {
   //     int v = q.front();
   //     q.pop();
   //     for (int u : G[v]) {
   //         if (!visited[u]) {
   //             visited[u] = 1;
   //             q.push(u);
   //             d[u] = d[v] + 1;
   //             p[u] = v;
   //         }
   //     }
   // }*/
   // bfs(q);
    //for (int i = 0; i < n; i++) {
    //    cout << d[i] << " ";
    //}
    //cout << "\n";
    //vector<int> path;
    //// ###########
    //int dest = 5;
    //if (visited[dest] == 0) {
    //    cout << "NO PATH\n";
    //}
    //else {
    //    int x = dest;
    //    while (x != -1) {
    //        path.push_back(x);
    //        x = p[x];
    //    }
    //    reverse(path.begin(), path.end());
    //}
    //for (int i = 0; i < path.size(); i++) {
    //    cout << path[i] << " ";
    //}
    //cout << endl;
}

void bfs(queue<int> q) {
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int u : G[v]) {
            if (!visited[u]) {
                visited[u] = 1;
                q.push(u);
                d[u] = d[v] + 1;
                p[u] = v;
            }
        }
    }
}
