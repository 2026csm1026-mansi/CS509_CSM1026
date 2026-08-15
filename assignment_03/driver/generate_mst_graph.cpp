

#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <random>
#include <algorithm>
#include <cstdint>

int main(int argc, char* argv[])
{
    if (argc < 4)
    {
        std::cerr << "Usage: " << argv[0] << " <V> <E> <output_file> [seed]" << std::endl;
        return 1;
    }

    long long V = std::stoll(argv[1]);
    long long E = std::stoll(argv[2]);
    std::string outPath = argv[3];
    unsigned seed = (argc >= 5) ? static_cast<unsigned>(std::stoul(argv[4])) : 42u;

    if (V <= 1)
    {
        std::cerr << "Error: V must be > 1" << std::endl;
        return 1;
    }
    long long minE = V - 1;
    if (E < minE)
    {
        std::cerr << "Warning: E too small for connectivity, bumping to V-1 = " << minE << std::endl;
        E = minE;
    }

    std::mt19937_64 rng(seed);
    std::uniform_int_distribution<int> weightDist(1, 100);
    std::uniform_int_distribution<long long> vertexDist(0, V - 1);

    // Edge set keyed as (min(a,b) * V + max(a,b)) to dedupe cheaply.
    std::vector<std::vector<std::pair<int, int>>> adj(V); // (neighbor, weight)
    std::set<long long> seen;

    auto edgeKey = [V](long long a, long long b) {
        if (a > b) std::swap(a, b);
        return a * V + b;
    };

    auto addEdge = [&](long long a, long long b) -> bool {
        if (a == b) return false;
        long long key = edgeKey(a, b);
        if (seen.count(key)) return false;
        seen.insert(key);
        int w = weightDist(rng);
        adj[a].push_back({static_cast<int>(b), w});
        adj[b].push_back({static_cast<int>(a), w});
        return true;
    };

    // 1) Guarantee connectivity: random permutation spanning chain.
    std::vector<long long> perm(V);
    for (long long i = 0; i < V; i++) perm[i] = i;
    std::shuffle(perm.begin(), perm.end(), rng);

    long long edgeCount = 0;
    for (long long i = 1; i < V; i++)
    {
        if (addEdge(perm[i - 1], perm[i])) edgeCount++;
    }

    // 2) Add random extra edges until target E is reached (sparse graph).
    long long attempts = 0;
    long long maxAttempts = E * 20 + 1000; // safety valve
    while (edgeCount < E && attempts < maxAttempts)
    {
        long long a = vertexDist(rng);
        long long b = vertexDist(rng);
        if (addEdge(a, b)) edgeCount++;
        attempts++;
    }

    // Write output file in Section 5.1 format.
    std::ofstream out(outPath);
    if (!out.is_open())
    {
        std::cerr << "Error: could not open output file " << outPath << std::endl;
        return 1;
    }

    out << V << " " << edgeCount << "\n";
    for (long long u = 0; u < V; u++)
    {
        out << u << " " << adj[u].size();
        for (auto& [n, w] : adj[u])
        {
            out << " " << n << " " << w;
        }
        out << "\n";
    }

    std::cerr << "Generated " << outPath << " : V=" << V << " E=" << edgeCount << std::endl;
    return 0;
}
