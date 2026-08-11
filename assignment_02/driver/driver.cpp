#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <chrono>
#include <limits>

#include "../src/bellman_ford.h"
#include "../src/floyd_warshall.h"

using namespace std;

const long long INF = numeric_limits<long long>::max() / 4;


// ============================================================
// Bellman-Ford input reader
// ============================================================

bool readBellmanFordInput(
    const string& filename,
    int& vertices,
    int& edges,
    vector<vector<pair<int, int>>>& adjacencyList,
    int& source)
{
    ifstream file(filename);

    if (!file)
    {
        cerr << "Error: could not open input file: "
             << filename << "\n";

        return false;
    }

    file >> vertices >> edges;

    if (!file || vertices <= 0 || edges < 0)
    {
        cerr << "Error: invalid Bellman-Ford header.\n";
        return false;
    }

    adjacencyList.resize(vertices);

    for (int i = 0; i < vertices; i++)
    {
        int vertex;
        int degree;

        file >> vertex >> degree;

        if (!file)
        {
            cerr << "Error: invalid adjacency-list input.\n";
            return false;
        }

        if (vertex < 0 || vertex >= vertices)
        {
            cerr << "Error: invalid vertex number.\n";
            return false;
        }

        if (degree < 0)
        {
            cerr << "Error: invalid degree.\n";
            return false;
        }

        for (int j = 0; j < degree; j++)
        {
            int neighbour;
            int weight;

            file >> neighbour >> weight;

            if (!file)
            {
                cerr << "Error: invalid edge data.\n";
                return false;
            }

            if (neighbour < 0 || neighbour >= vertices)
            {
                cerr << "Error: invalid neighbour vertex.\n";
                return false;
            }

            adjacencyList[vertex].push_back(
                {neighbour, weight}
            );
        }
    }

    string sourceWord;
    file >> sourceWord >> source;

    if (!file || sourceWord != "SOURCE")
    {
        cerr << "Error: SOURCE line missing.\n";
        return false;
    }

    if (source < 0 || source >= vertices)
    {
        cerr << "Error: invalid source vertex.\n";
        return false;
    }

    return true;
}


// ============================================================
// Floyd-Warshall input reader
// ============================================================

bool readFloydWarshallInput(
    const string& filename,
    int& vertices,
    vector<vector<long long>>& matrix)
{
    ifstream file(filename);

    if (!file)
    {
        cerr << "Error: could not open input file: "
             << filename << "\n";

        return false;
    }

    file >> vertices;

    if (!file || vertices <= 0)
    {
        cerr << "Error: invalid number of vertices.\n";
        return false;
    }

    matrix.assign(
        vertices,
        vector<long long>(vertices, INF)
    );

    for (int i = 0; i < vertices; i++)
    {
        for (int j = 0; j < vertices; j++)
        {
            string value;

            file >> value;

            if (!file)
            {
                cerr << "Error: incomplete Floyd-Warshall matrix.\n";
                return false;
            }

            if (value == "INF")
            {
                matrix[i][j] = INF;
            }
            else
            {
                try
                {
                    matrix[i][j] = stoll(value);
                }
                catch (...)
                {
                    cerr << "Error: invalid matrix value.\n";
                    return false;
                }
            }
        }
    }

    return true;
}


// ============================================================
// Run Bellman-Ford
// ============================================================
int runBellmanFord(const string& filename)
{
    int vertices;
    int edges;
    int source;

    vector<vector<pair<int, int>>> adjacencyList;

    if (!readBellmanFordInput(
            filename,
            vertices,
            edges,
            adjacencyList,
            source))
    {
        return 1;
    }

    // CSR conversion is preprocessing.
    // It is intentionally outside the timed region.
    CSRGraph graph = convertToCSR(adjacencyList);

    // --------------------------------------------------------
    // Algorithm timing starts here.
    // --------------------------------------------------------

    auto start = chrono::high_resolution_clock::now();

    BellmanFordResult result =
        bellmanFord(graph, source, vertices);

    auto stop = chrono::high_resolution_clock::now();

    double executionTime =
        chrono::duration<double, milli>(stop - start).count();

    // --------------------------------------------------------
    // Output summary only.
    // --------------------------------------------------------

    cout << "Algorithm: Bellman-Ford\n";
    cout << "Source: " << source << "\n";
    cout << "Vertices: " << vertices << "\n";
    cout << "Edges: " << edges << "\n";

    if (result.negativeCycle)
    {
        cout << "Negative cycle: true\n";
    }
    else
    {
        cout << "Negative cycle: none\n";
    }

    cout << "Execution time: "
         << executionTime
         << " ms\n";

    return 0;
}

// ============================================================
// Run Floyd-Warshall
// ============================================================
int runFloydWarshall(const string& filename)
{
    int vertices;

    vector<vector<long long>> matrix;

    if (!readFloydWarshallInput(
            filename,
            vertices,
            matrix))
    {
        return 1;
    }

    // --------------------------------------------------------
    // Algorithm timing starts here.
    // Input reading is NOT included.
    // --------------------------------------------------------

    auto start = chrono::high_resolution_clock::now();

    FloydWarshallResult result =
        floydWarshall(matrix);

    auto stop = chrono::high_resolution_clock::now();

    double executionTime =
        chrono::duration<double, milli>(stop - start).count();

    // --------------------------------------------------------
    // Output only summary information.
    // Do NOT print the complete matrix.
    // --------------------------------------------------------

    cout << "Algorithm: Floyd-Warshall\n";

    if (result.negativeCycle)
    {
        cout << "Negative cycle: true\n";
    }
    else
    {
        cout << "Negative cycle: none\n";
    }

    cout << "Vertices: "
         << vertices
         << "\n";

    cout << "Execution time: "
         << executionTime
         << " ms\n";

    return 0;
}



// ============================================================
// Main
// ============================================================

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        cerr << "Usage:\n";
        cerr << "  driver.exe bellman-ford <input-file>\n";
        cerr << "  driver.exe floyd-warshall <input-file>\n";

        return 1;
    }

    string algorithm = argv[1];
    string filename = argv[2];

    if (algorithm == "bellman-ford")
    {
        return runBellmanFord(filename);
    }

    if (algorithm == "floyd-warshall")
    {
        return runFloydWarshall(filename);
    }

    cerr << "Error: unknown algorithm: "
         << algorithm << "\n";

    return 1;
}