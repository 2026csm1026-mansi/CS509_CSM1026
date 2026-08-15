#include "prim.h"
#include <queue>
#include <tuple>
#include <vector>

MSTResult primMST(const CSRGraph& graph, int V, int startVertex)
{
    MSTResult result;
    if (V == 0) return result;
    using Node = std::tuple<long long, int, int>;
    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> pq;

    std::vector<bool> inMST(V, false);

    pq.push({0, startVertex, -1});

    int edgesAdded = 0;
    result.edges.reserve(V > 0 ? V - 1 : 0);

    while (!pq.empty() && edgesAdded < V - 1)
    {
        auto [w, u, parent] = pq.top();
        pq.pop();

        if (inMST[u]) continue;
        inMST[u] = true;

        if (parent != -1)
        {
            result.edges.push_back({parent, u, w});
            result.totalWeight += w;
            edgesAdded++;
        }
        for (int idx = graph.row_ptr[u]; idx < graph.row_ptr[u + 1]; idx++)
        {
            int v = graph.col_idx[idx];
            int weight = graph.values[idx];
            if (!inMST[v])
            {
                pq.push({weight, v, u});
            }
        }
    }
    return result;
}
