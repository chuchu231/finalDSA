// C++ program to print all paths of source to
// destination in given graph
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// utility function for printing
// the found path in graph
void printpath(vector<int>& path)
{
    int size = path.size();
    for (int i = 0; i < size; i++)
        cout << path[i] << " ";
    cout << endl;
}

// utility function to check if current
// vertex is already present in path
int isNotVisited(int x, vector<int>& path)
{
    int size = path.size();
    for (int i = 0; i < size; i++)
        if (path[i] == x)
            return 0;
    return 1;
}

// utility function for finding paths in graph
// from source to destination
void findpaths(vector<vector<int> >& g, int src, int dst, int v)
{
    // create a queue which stores
    // the paths
    queue<vector<int> > q;

    // path vector to store the current path
    vector<int> path;
    path.push_back(src);
    q.push(path);
    while (!q.empty()) {
        path = q.front();
        q.pop();
        int last = path[path.size() - 1];

        // if last vertex is the desired destination
        // then print the path
        if (last == dst)
            printpath(path);

        // traverse to all the nodes connected to
        // current vertex and push new path to queue
        for (int i = 0; i < g[last].size(); i++) {
            if (isNotVisited(g[last][i], path)) {
                vector<int> newpath(path);
                newpath.push_back(g[last][i]);
                q.push(newpath);
            }
        }
    }
}

void addEdge(vector<vector<int> > g,int u, int v)
{
    g[u].push_back(v);
    g[v].push_back(u);
}

// driver program
int main()
{
    vector<vector<int> > g;
    // number of vertices
    int v = 0;
    cout << "Enter the number of V: ";
    cin >> v;
    int edge = 0;
    cout << "Enter the number of E: ";
    cin >> edge;
    g.resize(v);
    while (edge--) {
        int x, y;
        cin >> x >> y;
        g[x].push_back(y);
        g[y].push_back(x);
    }

    int src = 0, dst = 0;
    cout << "Enter a and b : ";
    cin >> src >> dst;
    cout << "path from src " << src << " to dst " << dst << " are \n";

    // function for finding the paths
    findpaths(g, src, dst, v);

    return 0;
}
