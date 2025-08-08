#include "UnweightedGraph.h"
#include <iostream>

using namespace std;
using namespace MyGraph;

int main()
{
    vector<vector<int>> edges = {{0, 1}, {0, 2}, {1, 3}, {2, 3}};
    UnweightedGraph g(4, true, edges);

    vector<int> bfs = g.doBfsTraversal(0);

    for (int node : bfs)
    {
        cout << node << " ";
    }
    cout << endl;

    return 0;
}
