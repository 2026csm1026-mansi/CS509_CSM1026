#ifndef MST_TYPES_H
#define MST_TYPES_H

#include <vector>

struct MSTEdge
{
    int u;
    int v;
    long long weight;
};

struct MSTResult
{
    std::vector<MSTEdge> edges;
    long long totalWeight = 0;
};

#endif
