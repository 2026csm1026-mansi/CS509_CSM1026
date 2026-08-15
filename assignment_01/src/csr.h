#ifndef CSR_H
#define CSR_H
#include <vector>
#include <utility>

struct CSRGraph
{
    std::vector<int> row_ptr;
    std::vector<int> col_idx;
    std::vector<int> values;
};

using WeightedAdjList = std::vector<std::vector<std::pair<int, int>>>;

// Weighted adjacency list → CSR
CSRGraph convertToCSR(const WeightedAdjList& adjacencyList);

// For an unweighted graph, every edge gets value 1.
CSRGraph convertToCSR(const std::vector<std::vector<int>>& adjacencyList);

#endif