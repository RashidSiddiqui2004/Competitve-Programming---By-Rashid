#include "UnweightedGraph.h"
#include <stdio.h>
#include <vector>
#include <queue>
#include <stack>
#include <stdexcept>
#include <limits>
#include <algorithm>

using namespace std;

namespace MyGraph
{
    UnweightedGraph::UnweightedGraph(const int _numberOfVertices, bool _isDirected, const vector<vector<int>> &edges)
        : numberOfVertices(_numberOfVertices), isDirected(_isDirected)
    {
        vertices.assign(_numberOfVertices, 0);
        adjList.assign(_numberOfVertices, vector<int>());

        for (auto &edge : edges)
        {
            int u = edge[0], v = edge[1];
            adjList[u].push_back(v);
            if (!isDirected)
            {
                adjList[v].push_back(u);
            }
        }
    }

    UnweightedGraph::~UnweightedGraph() {}

    vector<int> UnweightedGraph::doBfsTraversal(int startNode)
    {
        if (startNode >= numberOfVertices || startNode < 0)
        {
            throw out_of_range("Start node must be within the range of existing vertices.");
        }

        vector<int> traversal;
        vector<bool> visited(numberOfVertices, false);
        queue<int> q;

        q.push(startNode);
        visited[startNode] = true;

        while (!q.empty())
        {
            int node = q.front();
            q.pop();
            traversal.push_back(node);

            for (int neighbor : adjList[node])
            {
                if (!visited[neighbor])
                {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }

        return traversal;
    }

    vector<int> UnweightedGraph::doDfsTraversal(int startNode)
    {
        if (startNode >= numberOfVertices || startNode < 0)
        {
            throw out_of_range("Start node must be within the range of existing vertices.");
        }

        vector<int> traversal;
        vector<bool> visited(numberOfVertices, false);
        stack<int> s;

        s.push(startNode);

        while (!s.empty())
        {
            int node = s.top();
            s.pop();

            if (!visited[node])
            {
                visited[node] = true;
                traversal.push_back(node);

                // Push neighbors in reverse for consistent left-to-right traversal
                for (auto it = adjList[node].rbegin(); it != adjList[node].rend(); ++it)
                {
                    if (!visited[*it])
                    {
                        s.push(*it);
                    }
                }
            }
        }

        return traversal;
    }

    vector<int> UnweightedGraph::shortestPathFromNode(int sourceNode)
    {
        if (sourceNode >= numberOfVertices || sourceNode < 0)
        {
            throw out_of_range("Source node must be within range.");
        }

        vector<int> distance(numberOfVertices, -1);
        queue<int> q;

        q.push(sourceNode);
        distance[sourceNode] = 0;

        while (!q.empty())
        {
            int node = q.front();
            q.pop();

            for (int neighbor : adjList[node])
            {
                if (distance[neighbor] == -1)
                {
                    distance[neighbor] = distance[node] + 1;
                    q.push(neighbor);
                }
            }
        }

        return distance;
    }

    vector<vector<int>> UnweightedGraph::pairwiseShortestPath()
    {
        const int INF = numeric_limits<int>::max() / 2;
        vector<vector<int>> dist(numberOfVertices, vector<int>(numberOfVertices, INF));

        for (int i = 0; i < numberOfVertices; ++i)
        {
            dist[i][i] = 0;
            for (int neighbor : adjList[i])
            {
                dist[i][neighbor] = 1;
            }
        }

        for (int k = 0; k < numberOfVertices; ++k)
        {
            for (int i = 0; i < numberOfVertices; ++i)
            {
                for (int j = 0; j < numberOfVertices; ++j)
                {
                    if (dist[i][k] + dist[k][j] < dist[i][j])
                    {
                        dist[i][j] = dist[i][k] + dist[k][j];
                    }
                }
            }
        }

        return dist;
    }

    vector<int> UnweightedGraph::topologicalSort()
    {
        vector<int> inDegree(numberOfVertices, 0);
        for (int i = 0; i < numberOfVertices; ++i)
        {
            for (int neighbor : adjList[i])
            {
                inDegree[neighbor]++;
            }
        }

        queue<int> q;
        for (int i = 0; i < numberOfVertices; ++i)
        {
            if (inDegree[i] == 0)
                q.push(i);
        }

        vector<int> topoOrder;
        while (!q.empty())
        {
            int node = q.front();
            q.pop();
            topoOrder.push_back(node);

            for (int neighbor : adjList[node])
            {
                inDegree[neighbor]--;
                if (inDegree[neighbor] == 0)
                {
                    q.push(neighbor);
                }
            }
        }

        if (topoOrder.size() != numberOfVertices)
        {
            throw runtime_error("Graph has a cycle; topological sort not possible.");
        }

        return topoOrder;
    }
}
