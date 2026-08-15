#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <string>
#include "../../assignment_01/src/csr.h"
#include "../src/kruskal.h"
#include "../src/prim.h"

static bool readMSTFile(const std::string& path, int& V, int& E, WeightedAdjList& adjList)
{
    std::ifstream in(path);
    if (!in.is_open())
    {
        std::cerr << "Error: could not open input file: " << path << std::endl;
        return false;
    }

    if (!(in >> V >> E) || V <= 0)
    {
        std::cerr << "Error: invalid or missing V/E header in " << path << std::endl;
        return false;
    }

    adjList.assign(V, {});

    for (int i = 0; i < V; i++)
    {
        int u, degree;
        if (!(in >> u >> degree))
        {
            std::cerr << "Error: malformed adjacency line for vertex " << i << std::endl;
            return false;
        }
        if (u < 0 || u >= V)
        {
            std::cerr << "Error: vertex id out of range: " << u << std::endl;
            return false;
        }

        adjList[u].reserve(degree);
        for (int k = 0; k < degree; k++)
        {
            int neighbor, weight;
            if (!(in >> neighbor >> weight))
            {
                std::cerr << "Error: malformed edge for vertex " << u << std::endl;
                return false;
            }
            if (neighbor < 0 || neighbor >= V)
            {
                std::cerr << "Error: neighbor out of range: " << neighbor << std::endl;
                return false;
            }
            adjList[u].push_back({neighbor, weight});
        }
    }

    return true;
}
    void printResult(const std::string& name, const MSTResult& result, double time) 
    {
    std::cout << "Algorithm: " << name << std::endl;
    std::cout << "Total MST weight: " << result.totalWeight << std::endl;
    std::cout << "Execution time: " << time << " ms" << std::endl;
    std::cout << std::endl;
}


int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <input_file.txt>" << std::endl;
        return 1;
    }

    std::string path = argv[1];

    int V = 0, E = 0;
    WeightedAdjList adjList;
    if (!readMSTFile(path, V, E, adjList))
    {
        return 1;
    }

    CSRGraph graph = convertToCSR(adjList); 

    auto k_start = std::chrono::high_resolution_clock::now();
    MSTResult kruskalResult = kruskalMST(graph, V);
    auto k_end = std::chrono::high_resolution_clock::now();
    double kruskalMs = std::chrono::duration<double, std::milli>(k_end - k_start).count();

    auto p_start = std::chrono::high_resolution_clock::now();
    MSTResult primResult = primMST(graph, V, 0);
    auto p_end = std::chrono::high_resolution_clock::now();
    double primMs = std::chrono::duration<double, std::milli>(p_end - p_start).count();

    printResult("Kruskal's MST", kruskalResult, kruskalMs);
    printResult("Prim's MST", primResult, primMs);

    if (kruskalResult.totalWeight != primResult.totalWeight)
    {
        std::cerr << "WARNING: Kruskal and Prim total weights differ! ("
                   << kruskalResult.totalWeight << " vs " << primResult.totalWeight
                   << ") — check graph connectivity." << std::endl;
    }

    return 0;
}
