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
└── readme.md
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

The following timings were obtained by running the algorithms through the **common wrapper**.

### Bellman-Ford

|       V |       E |       Time |
| ------: | ------: | ---------: |
|      10 |      30 |  0.0196 ms |
|     100 |     300 |   0.062 ms |
|  10,000 |  30,000 |  8.9985 ms |
|  50,000 | 150,000 |  79.708 ms |
| 100,000 | 300,000 | 224.884 ms |

### Floyd-Warshall

|     V |        Time |
| ----: | ----------: |
|    10 |   0.0119 ms |
|   100 |   7.8064 ms |
|   500 |  782.408 ms |
| 1,000 | 7,102.54 ms |
| 2,000 | 53,386.2 ms |

All benchmark tests completed successfully, with **no negative cycle detected** in the generated test cases.

> Execution times may vary depending on system load and hardware.
>
> Bellman-Ford scales approximately with **O(VE)**, while Floyd-Warshall scales with **O(V³)**. The significantly larger execution time for Floyd-Warshall on larger graphs is consistent with its cubic time complexity.
