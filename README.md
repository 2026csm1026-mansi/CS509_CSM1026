# CS509 Laboratory Repository

## Repository Overview

This repository contains the laboratory assignments for the CS509 course.

The repository is maintained for the M.Tech CSE program and contains individual
and, where applicable, buddy assignments completed according to the CS509
laboratory guidelines.

The current repository contains Assignment 01.

### Assignment 01

Assignment 01 contains the following individual work:

- GEMM (General Matrix-Matrix Multiplication)
  - Simple GEMM
  - Blocking GEMM
- CSR (Compressed Sparse Row) graph representation and adjacency-list-to-CSR conversion

The implementations are written in C++ and include dedicated driver programs
for testing correctness and measuring algorithm execution time. 


## Student Details

### Individual Assignment

- Name: Mansi Verma
- Entry Number: CSM1026
- Assignment Mode: Individual
- Course: CS509
- Program: M.Tech CSE

## Language and Environment

- Programming Language: C++
- C++ Standard: C++17
- Compiler: g++
- Compilation Flags: `-std=c++17 -Wall -Wextra`
- Operating System: Windows


## Directory Structure

```text
CS509_CSM1026/
├── README.md
└── assignment_01/
    ├── driver/
    │   ├── gemm_test.cpp
    │   └── csr_test.cpp
    │
    ├── src/
    │   ├── gemm_simple.cpp
    │   ├── gemm_simple.h
    │   ├── gemm_blocked.cpp
    │   ├── gemm_blocked.h
    │   ├── csr.cpp
    │   └── csr.h
    │
    └── tests/
        ├── gemm_test_01.txt
        ├── gemm_test_02.txt
        ├── gemm_test_03.txt
        ├── gemm_test_04.txt
        ├── csr_test_01.txt
        ├── csr_test_01_expected.txt
        ├── csr_test_02.txt
        ├── csr_test_02_expected.txt
        ├── csr_test_03.txt
        └── csr_test_03_expected.txt


---

# Step 5 — Assignment 01 section

Then:

```markdown
# Assignment 01 - GEMM and CSR

## Assignment Mode

Individual

## Objective

The objective of Assignment 01 is to implement and evaluate:

1. Simple GEMM
2. Blocking GEMM
3. Adjacency-list-to-CSR conversion

The GEMM implementations must produce the same result for the same matrix
input. The execution time of the two implementations is measured separately.

The CSR implementation converts an adjacency-list representation into the
Compressed Sparse Row (CSR) representation consisting of:

- `row_ptr`
- `col_idx`
- `values`



## GEMM

### Objective

GEMM (General Matrix-Matrix Multiplication) computes the product of two
matrices.

For:

- A of size `M × K`
- B of size `K × N`

the resulting matrix C has size `M × N`.

Each element is computed as:

C[i][j] = Σ A[i][k] × B[k][j]

for `k = 0 ... K-1`.

### Simple GEMM

The simple implementation uses the direct nested-loop matrix multiplication
approach.

### Blocking GEMM

The blocking implementation divides the matrices into smaller blocks or tiles.
The purpose of blocking is to improve data reuse and cache locality by
processing smaller portions of the matrices at a time.



## GEMM Input Format

Each GEMM test file contains one test case.

The first line contains:

```text
M K N




---

## Step 8 — Timing methodology

This is an important section because your professor specifically emphasized it.

Add:

```markdown
## Runtime Measurement

Execution time is measured using `std::chrono::steady_clock`.

Only the execution of the GEMM algorithm is included in the measured region.

The following operations are excluded from the measured time:

- Input file reading
- Matrix input parsing
- Matrix preparation
- Result printing
- Output formatting
- Correctness checking

The timer starts immediately before the GEMM function is called and stops
immediately after the function returns.

Each GEMM implementation is executed 3 times for timing, and the average
execution time is reported.

Execution time is reported in milliseconds (ms).
