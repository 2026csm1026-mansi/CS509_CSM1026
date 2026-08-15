#include "kruskal.h"
#include <algorithm>
#include <numeric>
namespace
{
    class DSU
    {
    public:
        explicit DSU(int n) : parent(n), rank_(n, 0)
        {
            std::iota(parent.begin(), parent.end(), 0);
        }

        int find(int x)
        {
            while (parent[x] != x)
            {
                parent[x] = parent[parent[x]]; // path compression
                x = parent[x];
            }
            return x;
        }

        // Returns true if a and b were in different components (union performed).
        bool unite(int a, int b)
        {
            int ra = find(a);
            int rb = find(b);
            if (ra == rb) return false;

            if (rank_[ra] < rank_[rb]) std::swap(ra, rb);
            parent[rb] = ra;
            if (rank_[ra] == rank_[rb]) rank_[ra]++;
            return true;
        }

    private:
        std::vector<int> parent;
        std::vector<int> rank_;
    };
}

MSTResult kruskalMST(const CSRGraph& graph, int V)
{
    MSTResult result;
    std::vector<MSTEdge> edges;
    edges.reserve(graph.col_idx.size() / 2);

    for (int u = 0; u < V; u++)
    {
        for (int idx = graph.row_ptr[u]; idx < graph.row_ptr[u + 1]; idx++)
        {
            int v = graph.col_idx[idx];
            int w = graph.values[idx];
            if (u < v)
            {
                edges.push_back({u, v, w});
            }
        }
    }
    std::sort(edges.begin(), edges.end(),
              [](const MSTEdge& a, const MSTEdge& b) { return a.weight < b.weight; });

    DSU dsu(V);
    result.edges.reserve(V > 0 ? V - 1 : 0);

    for (const auto& e : edges)
    {
        if (static_cast<int>(result.edges.size()) == V - 1) break;

        if (dsu.unite(e.u, e.v))
        {
            result.edges.push_back(e);
            result.totalWeight += e.weight;
        }
    }

    return result;
}
