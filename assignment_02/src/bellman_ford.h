#ifndef BELLMAN_FORD_H
#define BELLMAN_FORD_H
#include <vector>
#include "../../assignment_01/src/csr.h"

struct BellmanFordResult
{
    std::vector<long long> distance;
    bool negativeCycle;
};
BellmanFordResult bellmanFord(const CSRGraph& graph,int source,int vertices);

#endif
