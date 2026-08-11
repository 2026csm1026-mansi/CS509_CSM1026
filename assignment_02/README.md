# CS509 – Assignment 2

## Graph Algorithms

Implementation and benchmarking of two shortest-path algorithms in **C++17**:

* **Bellman-Ford** – single-source shortest paths
* **Floyd-Warshall** – all-pairs shortest paths

Both implementations include negative-cycle detection and execution-time measurement.

## Structure

```text
assignment_02/
├── driver/
│   ├── driver.cpp
│   └── generate_tests.cpp
├── src/
│   ├── bellman_ford.cpp
│   ├── bellman_ford.h
│   ├── floyd_warshall.cpp
│   └── floyd_warshall.h
├── tests/
└── README.md
```

## Complexity

| Algorithm      | Time  | Space    |
| -------------- | ----- | -------- |
| Bellman-Ford   | O(VE) | O(V + E) |
| Floyd-Warshall | O(V³) | O(V²)    |

## Compilation

From the repository root:

```powershell
g++ -std=c++17 assignment_02\driver\driver.cpp assignment_02\src\bellman_ford.cpp assignment_02\src\floyd_warshall.cpp assignment_01\src\csr.cpp -o assignment_02\driver\assignment2.exe
```

## Running

### Bellman-Ford

```powershell
.\assignment_02\driver\assignment2.exe bellman-ford assignment_02\tests\bf_100.txt
```

### Floyd-Warshall

```powershell
.\assignment_02\driver\assignment2.exe floyd-warshall assignment_02\tests\fw_100.txt
```

## Test Generation

Compile and run:

```powershell
g++ -std=c++17 assignment_02\driver\generate_tests.cpp -o assignment_02\driver\generate_tests.exe

.\assignment_02\driver\generate_tests.exe
```

Generated test cases cover:

* **Bellman-Ford:** 10 to 100,000 vertices
* **Floyd-Warshall:** 10 to 2,000 vertices

## Benchmark Results

### Bellman-Ford

|       V |       E |       Time |
| ------: | ------: | ---------: |
|      10 |      30 |  0.0029 ms |
|     100 |     300 |  0.0493 ms |
|  10,000 |  30,000 |  5.2375 ms |
|  50,000 | 150,000 | 29.9243 ms |
| 100,000 | 300,000 |  64.309 ms |

### Floyd-Warshall

|     V |       Time |
| ----: | ---------: |
|    10 |  0.0138 ms |
|   100 |  3.1719 ms |
|   500 | 367.464 ms |
| 1,000 | 3027.33 ms |
| 2,000 | 24843.9 ms |

> Execution times may vary depending on system load and hardware.
