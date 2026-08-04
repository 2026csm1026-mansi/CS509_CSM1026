#include "csr.h"

CSRGraph convertToCSR(const WeightedAdjList& adjacencyList)
{
    CSRGraph graph;

    std::size_t vertices = adjacencyList.size();

    // row_ptr has V + 1 entries.
    graph.row_ptr.resize(vertices + 1);

    graph.row_ptr[0] = 0;

    // Build cumulative row offsets.
    for (std::size_t i = 0; i < vertices; i++)
    {
        graph.row_ptr[i + 1] =
            graph.row_ptr[i] + adjacencyList[i].size();
    }

    // Total number of edges.
    std::size_t edges = graph.row_ptr[vertices];

    graph.col_idx.reserve(edges);
    graph.values.reserve(edges);

    // Store destination vertices and corresponding weights.
    for (std::size_t i = 0; i < vertices; i++)
    {
        for (const auto& edge : adjacencyList[i])
        {
            graph.col_idx.push_back(edge.first);
            graph.values.push_back(edge.second);
        }
    }

    return graph;
}

CSRGraph convertToCSR(const std::vector<std::vector<int>>& adjacencyList)
{
    CSRGraph graph;

    std::size_t vertices = adjacencyList.size();

    graph.row_ptr.resize(vertices + 1);

    graph.row_ptr[0] = 0;

    // Build cumulative row offsets.
    for (std::size_t i = 0; i < vertices; i++)
    {
        graph.row_ptr[i + 1] =
            graph.row_ptr[i] + adjacencyList[i].size();
    }

    std::size_t edges = graph.row_ptr[vertices];

    graph.col_idx.reserve(edges);
    graph.values.reserve(edges);

    // Store neighbours.
    // Every edge gets weight 1.
    for (std::size_t i = 0; i < vertices; i++)
    {
        for (int neighbour : adjacencyList[i])
        {
            graph.col_idx.push_back(neighbour);
            graph.values.push_back(1);
        }
    }

    return graph;
}