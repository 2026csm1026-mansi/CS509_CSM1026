#ifndef GEMM_SIMPLE_H
#define GEMM_SIMPLE_H

#include <vector>

using Matrix = std::vector<std::vector<int>>;

Matrix gemmSimple(const Matrix &A , const Matrix &B);

#endif