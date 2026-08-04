#include "gemm_blocked.h"

#include <algorithm>
#include <stdexcept>

Matrix gemmBlocked(
    const Matrix& A,
    const Matrix& B,
    int blockSize
)
{
    if (blockSize <= 0)
    {
        throw std::invalid_argument(
            "Block size must be greater than zero"
        );
    }

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

    for (std::size_t a = 0; a < m; a += blockSize)
    {
        for (std::size_t b = 0; b < n; b += blockSize)
        {
            for (std::size_t c = 0; c < k; c += blockSize)
            {
                std::size_t iEnd =
                    std::min(a + static_cast<std::size_t>(blockSize), m);

                std::size_t jEnd =
                    std::min(b + static_cast<std::size_t>(blockSize), n);

                std::size_t lEnd =
                    std::min(c + static_cast<std::size_t>(blockSize), k);

                for (std::size_t i = a; i < iEnd; i++)
                {
                    for (std::size_t j = b; j < jEnd; j++)
                    {
                        for (std::size_t l = c; l < lEnd; l++)
                        {
                            C[i][j] += A[i][l] * B[l][j];
                        }
                    }
                }
            }
        }
    }

    return C;
}