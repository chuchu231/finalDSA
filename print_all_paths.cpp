
#include <iostream>
#include <vector>
#include <queue>
using namespace std;


void printpath(vector<int>& path)
{
    int size = path.size();
    for (int i = 0; i < size; i++)
        cout << path[i] << " ";
    cout << endl;
}


int isNotVisited(int x, vector<int>& path)
{
    int size = path.size();
    for (int i = 0; i < size; i++)
        if (path[i] == x)
            return 0;
    return 1;
}

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

// program
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
