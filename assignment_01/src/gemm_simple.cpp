#include "gemm_simple.h"

#include <stdexcept>

Matrix gemmSimple(const Matrix& A, const Matrix& B)
{
    if (A.empty() || B.empty())
    {
        return {};
    }

    std::size_t m = A.size();
    std::size_t k = A[0].size();
    std::size_t n = B[0].size();

    if (k != B.size())
    {
        throw std::invalid_argument(
            "Matrix dimensions are incompatible"
        );
    }

    Matrix C(m, std::vector<int>(n, 0));

    for (std::size_t i = 0; i < m; i++)
    {
        for (std::size_t j = 0; j < n; j++)
        {
            for (std::size_t l = 0; l < k; l++)
            {
                C[i][j] += A[i][l] * B[l][j];
            }
        }
    }

    return C;
}