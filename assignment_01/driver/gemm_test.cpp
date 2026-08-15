#include <iostream>
#include <fstream>
#include <chrono>
#include <stdexcept>
#include <algorithm>
#include "../src/gemm_simple.h"
#include "../src/gemm_blocked.h"


void printMatrix(const Matrix& matrix)
{
    size_t limit = 5;

    for (size_t i = 0; i < std::min(matrix.size(), limit); i++)
    {
        for (size_t j = 0; j < std::min(matrix[i].size(), limit); j++)
        {
            std::cout << matrix[i][j] << " ";
        }

        std::cout << "\n";
    }

    if (!matrix.empty() && 
        (matrix.size() > limit || matrix[0].size() > limit))
    {
        std::cout << "... matrix truncated ..." << "\n";
    }
}


int main(int argc, char* argv[])
{
    const int repetitions = 3;

    if (argc != 3)
    {
        std::cerr
            << "Usage: gemm_test <input_file> <block_size>\n";
        return 1;
    }

    std::ifstream input(argv[1]);

    if (!input)
    {
        std::cerr
            << "Error: could not open test file\n";
        return 1;
    }

    int blockSize;

    try
    {
        blockSize = std::stoi(argv[2]);
    }
    catch (const std::exception&)
    {
        std::cerr
            << "Error: invalid block size\n";
        return 1;
    }

    if (blockSize <= 0)
    {
        std::cerr
            << "Error: block size must be greater than zero\n";
        return 1;
    }

    int m;
    int k;
    int n;

    if (!(input >> m >> k >> n))
    {
        std::cerr
            << "Error: could not read m, k, n from test file\n";
        return 1;
    }

    if (m <= 0 || k <= 0 || n <= 0)
    {
        std::cerr
            << "Error: matrix dimensions must be positive\n";
        return 1;
    }

    Matrix A(m, std::vector<int>(k));
    Matrix B(k, std::vector<int>(n));

    // Read matrix A.
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < k; j++)
        {
            if (!(input >> A[i][j]))
            {
                std::cerr
                    << "Error: invalid matrix A data\n";
                return 1;
            }
        }
    }

    // Read matrix B.
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (!(input >> B[i][j]))
            {
                std::cerr
                    << "Error: invalid matrix B data\n";
                return 1;
            }
        }
    }


    // --------------------------------------------------
    // Correctness check
    // --------------------------------------------------

    Matrix simpleResult = gemmSimple(A, B);
    Matrix blockedResult = gemmBlocked(A, B, blockSize);

    if (simpleResult == blockedResult)
    {
        std::cout
            << "PASS: Simple and blocked results match.\n";
    }
    else
    {
        std::cout
            << "FAIL: Simple and blocked results do not match.\n";
        return 1;
    }


    // --------------------------------------------------
    // Print results
    // --------------------------------------------------

    std::cout << "\nAlgorithm: GEMM Simple\n";
    std::cout << "Result matrix:\n";
    printMatrix(simpleResult);

    std::cout << "\nAlgorithm: GEMM Blocked\n";
    std::cout << "Result matrix:\n";
    printMatrix(blockedResult);


    // --------------------------------------------------
    // Simple GEMM timing
    // --------------------------------------------------

    double totalSimpleTime = 0.0;

    for (int r = 0; r < repetitions; r++)
    {
        auto start = std::chrono::steady_clock::now();

        Matrix result = gemmSimple(A, B);

        auto end = std::chrono::steady_clock::now();

        std::chrono::duration<double, std::milli> elapsed =
            end - start;

        totalSimpleTime += elapsed.count();

        // Prevent the result from being considered completely unused.
        volatile int check = result[0][0];
        (void)check;
    }

    double simpleTime =
        totalSimpleTime / repetitions;


    // --------------------------------------------------
    // Blocked GEMM timing
    // --------------------------------------------------

    double totalBlockedTime = 0.0;

    for (int r = 0; r < repetitions; r++)
    {
        auto start = std::chrono::steady_clock::now();

        Matrix result = gemmBlocked(A, B, blockSize);

        auto end = std::chrono::steady_clock::now();

        std::chrono::duration<double, std::milli> elapsed =
            end - start;

        totalBlockedTime += elapsed.count();

        // Prevent the result from being considered completely unused.
        volatile int check = result[0][0];
        (void)check;
    }

    double blockedTime =
        totalBlockedTime / repetitions;


    // --------------------------------------------------
    // Timing output
    // --------------------------------------------------

    std::cout
        << "\nSimple GEMM average time: "
        << simpleTime
        << " ms\n";

    std::cout
        << "Blocked GEMM average time: "
        << blockedTime
        << " ms\n";

    std::cout
        << "Block size: "
        << blockSize
        << "\n";


    return 0;
}