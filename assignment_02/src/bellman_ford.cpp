#include "bellman_ford.h"
#include <limits>

BellmanFordResult bellmanFord(const CSRGraph& graph,int source,int vertices)
{
    const long long INF = std::numeric_limits<long long>::max() / 4;
    std::vector<long long> distance(vertices, INF);
    distance[source] = 0;
    for (int iteration = 0; iteration < vertices - 1; iteration++)
    {
        bool changed = false;
        for (int u = 0; u < vertices; u++)
        {
            if (distance[u] == INF)
                continue;
            for (int index = graph.row_ptr[u];index < graph.row_ptr[u + 1];index++)
            {
                int v = graph.col_idx[index];
                int weight = graph.values[index];

                if (distance[u] + weight < distance[v])
                {
                    distance[v] = distance[u] + weight;
                    changed = true;
                }
            }
        }
        if (!changed)
            break;
    }
    bool negativeCycle = false;

    for (int u = 0; u < vertices; u++)
    {
        if (distance[u] == INF)
            continue;
        for (int index = graph.row_ptr[u];
             index < graph.row_ptr[u + 1];
             index++)
        {
            int v = graph.col_idx[index];
            int weight = graph.values[index];

            if (distance[u] + weight < distance[v])
            {
                negativeCycle = true;
                break;
            }
        }
        if (negativeCycle)
            break;
    }
    return {distance, negativeCycle};
}