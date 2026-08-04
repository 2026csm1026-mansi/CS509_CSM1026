# CS509 Laboratory Repository

## Repository Overview

This repository contains the CS509 laboratory assignments for the M.Tech CSE
program. The current repository contains Assignment 01 implemented individually.

## Student Details

| Field | Details |
|-------|---------|
| Name  | Mansi Verma |
| Entry Number | CSM1026 |
| Course | CS509 |
| Program | M.Tech CSE |
| Mode | Individual |
| Language | C++17 |

## Environment

- Compiler: `g++`
- Standard: C++17
- Flags: `-std=c++17 -Wall -Wextra`
- OS: Windows

## Directory Structure

```text
CS509_CSM1026/
├── README.md
├── .gitignore
├── common_wrapper/
│   └── wrapper.cpp
└── assignment_01/
    ├── src/
    │   ├── gemm_simple.cpp
    │   ├── gemm_simple.h
    │   ├── gemm_blocked.cpp
    │   ├── gemm_blocked.h
    │   ├── csr.cpp
    │   └── csr.h
    ├── driver/
    │   ├── gemm_test.cpp
    │   └── csr_test.cpp
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



## Test Cases and Results

The following tables document every test case included in Assignment 01.

### GEMM Results

| Test File          |  Input Type / Size                       | Expected Output       | Actual Output                           | Simple Time (ms)  | Blocking Time (ms) | Block Size | Status |
|--------------------|------------------------------------------|---------------------=-|-----------------------------------------|----------:|---------------------:|----------|--------|
| `gemm_test_01.txt` | A: 2×3, B: 3×2, C: 2×2                   | `58 64 / 139 154`     | Simple = Blocking = `58 64 / 139 154`   | 0.0022       | 0.000633           | 8          | PASS   |
| `gemm_test_02.txt` | A: 64×64, B: 64×64, C: 64×64             | All elements = `64`   | Simple = Blocking; all elements = `64`  | 3.51667      | 3.84423            | 8          | PASS   |
| `gemm_test_03.txt` | A: 128×128, B: 128×128, C: 128×128       | All elements = `128`  | Simple = Blocking; all elements = `128`  | 27.7589       | 29.1609            | 8          | PASS   |
| `gemm_test_04.txt` | A: 1000×1000, B: 1000×1000, C: 1000×1000 | All elements = `1000` | Simple = Blocking; all elements = `1000` | 15472.8          | 14779              | 8          | PASS   |


### CSR Results

| Algorithm      | Test File         | Vertices | Edges | Input Type              | Expected Output                                   | Actual Output      | Time | Status |
|----------------|-------------------|----------|------:|-------------------------|---------------------------------------------------|-------------------|------|---------|
| CSR Conversion | `csr_test_01.txt` | 4        | 6     | Weighted adjacency list | `row_ptr`, `col_idx`, `values` match expected CSR | All three arrays match | N/A  | PASS    |
| CSR Conversion | `csr_test_02.txt` | 5        | 5     | Weighted adjacency list | `row_ptr`, `col_idx`, `values` match expected CSR | All three arrays match | N/A  | PASS    |
| CSR Conversion | `csr_test_03.txt` | 4        | 0     | Weighted adjacency list | Empty `col_idx` and `values`; correct `row_ptr`   | All arrays match       | N/A  | PASS     |

