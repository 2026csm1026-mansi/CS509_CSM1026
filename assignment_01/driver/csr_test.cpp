#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>

#include "../src/csr.h"

void printVector(const std::string& name, const std::vector<int>& v)
{
    std::cout << name << ": ";

    for (int value : v)
    {
        std::cout << value << " ";
    }

    std::cout << "\n";
}

std::vector<int> parseLine(const std::string& line)
{
    std::vector<int> result;
    std::stringstream ss(line);

    int value;

    while (ss >> value)
    {
        result.push_back(value);
    }

    return result;
}

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        std::cerr
            << "Usage: csr_test <input_file> <expected_file>\n";

        return 1;
    }

    // --------------------------------------------------
    // Open graph input
    // --------------------------------------------------

    std::ifstream input(argv[1]);

    if (!input)
    {
        std::cerr << "Error: could not open input file\n";
        return 1;
    }

    int vertices;
    int edges;

    if (!(input >> vertices >> edges))
    {
        std::cerr << "Error: could not read vertices and edges\n";
        return 1;
    }

    WeightedAdjList adjacencyList(vertices);

    // --------------------------------------------------
    // Read adjacency list
    // --------------------------------------------------

    for (int i = 0; i < vertices; i++)
    {
        int vertex;
        int degree;

        if (!(input >> vertex >> degree))
        {
            std::cerr << "Error: invalid vertex information\n";
            return 1;
        }

        for (int j = 0; j < degree; j++)
        {
            int neighbour;
            int weight;

            if (!(input >> neighbour >> weight))
            {
                std::cerr << "Error: invalid edge information\n";
                return 1;
            }

            adjacencyList[vertex].push_back(
                {neighbour, weight}
            );
        }
    }

    // --------------------------------------------------
    // Convert to CSR
    // --------------------------------------------------

    CSRGraph graph = convertToCSR(adjacencyList);

    // --------------------------------------------------
    // Read expected CSR
    // --------------------------------------------------

    std::ifstream expectedFile(argv[2]);

    if (!expectedFile)
    {
        std::cerr << "Error: could not open expected file\n";
        return 1;
    }
int rowPtrSize;
int colIdxSize;
int valuesSize;

expectedFile >> rowPtrSize;

std::vector<int> expectedRowPtr(rowPtrSize);

for (int i = 0; i < rowPtrSize; i++)
{
    expectedFile >> expectedRowPtr[i];
}

expectedFile >> colIdxSize;

std::vector<int> expectedColIdx(colIdxSize);

for (int i = 0; i < colIdxSize; i++)
{
    expectedFile >> expectedColIdx[i];
}

expectedFile >> valuesSize;

std::vector<int> expectedValues(valuesSize);

for (int i = 0; i < valuesSize; i++)
{
    expectedFile >> expectedValues[i];
}
    // --------------------------------------------------
    // Print actual
    // --------------------------------------------------

    std::cout << "Actual CSR:\n";

    printVector("row_ptr", graph.row_ptr);
    printVector("col_idx", graph.col_idx);
    printVector("values ", graph.values);

    // --------------------------------------------------
    // Print expected
    // --------------------------------------------------

    std::cout << "\nExpected CSR:\n";

    printVector("row_ptr", expectedRowPtr);
    printVector("col_idx", expectedColIdx);
    printVector("values ", expectedValues);

    // --------------------------------------------------
    // Compare
    // --------------------------------------------------

    bool rowPtrCorrect =
        graph.row_ptr == expectedRowPtr;

    bool colIdxCorrect =
        graph.col_idx == expectedColIdx;

    bool valuesCorrect =
        graph.values == expectedValues;

    std::cout << "\nComparison:\n";

    if (rowPtrCorrect)
        std::cout << "PASS: row_ptr matches.\n";
    else
        std::cout << "FAIL: row_ptr does not match.\n";

    if (colIdxCorrect)
        std::cout << "PASS: col_idx matches.\n";
    else
        std::cout << "FAIL: col_idx does not match.\n";

    if (valuesCorrect)
        std::cout << "PASS: values matches.\n";
    else
        std::cout << "FAIL: values does not match.\n";

    // --------------------------------------------------
    // Final result
    // --------------------------------------------------

    if (rowPtrCorrect &&
        colIdxCorrect &&
        valuesCorrect)
    {
        std::cout << "\nPASS: CSR conversion is correct.\n";
    }
    else
    {
        std::cout << "\nFAIL: CSR conversion is incorrect.\n";
        return 1;
    }

    return 0;
}