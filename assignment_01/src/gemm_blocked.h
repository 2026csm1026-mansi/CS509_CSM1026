#ifndef GEMM_BLOCKED_H
#define GEMM_BLOCKED_H

#include "gemm_simple.h"

Matrix gemmBlocked(
    const Matrix& A , 
    const Matrix& B , 
    int blockSize);

#endif