#ifndef UNWEIGHTED_GRAPH_H
#define UNWEIGHTED_GRAPH_H

#include <vector>

namespace MyGraph
{
    class UnweightedGraph
    {
    private:
        int numberOfVertices;
        std::vector<int> vertices;
        std::vector<std::vector<int>> adjList;
        bool isDirected;

    public:
        UnweightedGraph(int _numberOfVertices, bool _isDirected, const std::vector<std::vector<int>> &edges);
        ~UnweightedGraph();

        std::vector<int> doBfsTraversal(int startNode);
        std::vector<int> doDfsTraversal(int startNode);
        std::vector<int> shortestPathFromNode(int sourceNode);
        std::vector<std::vector<int>> pairwiseShortestPath();
        std::vector<int> topologicalSort();
    };

} // namespace MyGraph

#endif // UNWEIGHTED_GRAPH_H
