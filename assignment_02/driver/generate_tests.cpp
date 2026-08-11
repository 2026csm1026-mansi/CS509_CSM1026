#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <string>
#include <filesystem>
using namespace std;
namespace fs = std::filesystem;

void generateBellmanFord(
    const fs::path& filename,
    int vertices,
    int edgesPerVertex)
{
    mt19937 rng(1000 + vertices);

    uniform_int_distribution<int> vertexDist(0, vertices - 1);
    uniform_int_distribution<int> weightDist(1, 20);

    int totalEdges = vertices * edgesPerVertex;

    vector<vector<pair<int, int>>> adjacency(vertices);

    for (int u = 0; u < vertices; u++)
    {
        for (int e = 0; e < edgesPerVertex; e++)
        {
            int v;

            do
            {
                v = vertexDist(rng);
            }
            while (v == u);

            int weight = weightDist(rng);

            adjacency[u].push_back({v, weight});
        }
    }

    ofstream file(filename);

    if (!file)
    {
        cerr << "Error creating file: "
             << filename.string()
             << endl;
        return;
    }

    file << vertices << " " << totalEdges << "\n";

    for (int u = 0; u < vertices; u++)
    {
        file << u << " " << adjacency[u].size();

        for (const auto& edge : adjacency[u])
        {
            file << " "
                 << edge.first
                 << " "
                 << edge.second;
        }

        file << "\n";
    }

    file << "SOURCE 0\n";

    file.close();

    cout << "Generated "
         << filename.string()
         << " (" << vertices
         << " vertices, "
         << totalEdges
         << " edges)\n";
}
void generateFloydWarshall(
    const fs::path& filename,
    int vertices)
{
    mt19937 rng(2000 + vertices);

    uniform_int_distribution<int> weightDist(-5, 20);
    uniform_real_distribution<double> probability(0.0, 1.0);

    vector<vector<long long>> matrix(
        vertices,
        vector<long long>(vertices, -1)
    );
    for (int i = 0; i < vertices; i++)
    {
        matrix[i][i] = 0;
    }
    for (int i = 0; i < vertices; i++)
    {
        for (int j = i + 1; j < vertices; j++)
        {
            if (probability(rng) < 0.25)
            {
                matrix[i][j] = weightDist(rng);
            }
        }
    }

    ofstream file(filename);

    if (!file)
    {
        cerr << "Error creating file: "
             << filename.string()
             << endl;
        return;
    }

    file << vertices << "\n";

    for (int i = 0; i < vertices; i++)
    {
        for (int j = 0; j < vertices; j++)
        {
            if (matrix[i][j] == -1)
            {
                file << "INF";
            }
            else
            {
                file << matrix[i][j];
            }

            if (j + 1 < vertices)
            {
                file << " ";
            }
        }

        file << "\n";
    }

    file.close();

    cout << "Generated "
         << filename.string()
         << " (" << vertices
         << " vertices)\n";
}
int main()
{
    cout << "========================================\n";
    cout << " Assignment 2 Test Generator\n";
    cout << "========================================\n\n";
    fs::path repoRoot = fs::current_path();

    fs::path assignment02 =
        repoRoot / "assignment_02";

    fs::path testsDirectory =
        assignment02 / "tests";
    fs::create_directories(testsDirectory);


    cout << "Repository root:\n"
         << repoRoot.string()
         << "\n\n";

    cout << "Test directory:\n"
         << testsDirectory.string()
         << "\n\n";
    cout << "Generating Bellman-Ford tests...\n\n";

    generateBellmanFord(
        testsDirectory / "bf_10.txt",
        10,
        3
    );

    generateBellmanFord(
        testsDirectory / "bf_100.txt",
        100,
        3
    );

    generateBellmanFord(
        testsDirectory / "bf_10000.txt",
        10000,
        3
    );

    generateBellmanFord(
        testsDirectory / "bf_50000.txt",
        50000,
        3
    );

    generateBellmanFord(
        testsDirectory / "bf_100000.txt",
        100000,
        3
    );
    cout << "\nGenerating Floyd-Warshall tests...\n\n";

    generateFloydWarshall(
        testsDirectory / "fw_10.txt",
        10
    );

    generateFloydWarshall(
        testsDirectory / "fw_100.txt",
        100
    );

    generateFloydWarshall(
        testsDirectory / "fw_500.txt",
        500
    );

    generateFloydWarshall(
        testsDirectory / "fw_1000.txt",
        1000
    );

    generateFloydWarshall(
        testsDirectory / "fw_2000.txt",
        2000
    );


    cout << "\n========================================\n";
    cout << " All test files generated successfully.\n";
    cout << "========================================\n";

    return 0;
}