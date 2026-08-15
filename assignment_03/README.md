# CS509 Assignment 3 — Minimum Spanning Tree

## Student Details
- **Name:** Mansi Verma
- **Roll No.:** CSM1026
- **Course:** CS509 

## Overview

This assignment implements two Minimum Spanning Tree (MST) algorithms for a weighted undirected graph:

- **Kruskal's Algorithm** — uses edge sorting and Disjoint Set Union (DSU).
- **Prim's Algorithm** — uses a min-priority queue and starts from vertex `0`.

The graph is represented using the **CSR (Compressed Sparse Row)** representation implemented in Assignment 1.

## Directory Structure

```text
assignment_03/
├── driver/
│   ├── driver_mst.cpp
│   └── generate_mst_graph.cpp
├── src/
│   ├── kruskal.cpp
│   ├── kruskal.h
│   ├── prim.cpp
│   ├── prim.h
│   └── mst_types.h
├── tests/
│   ├── mst_10.txt
│   ├── mst_100.txt
│   ├── mst_10000.txt
│   ├── mst_50000.txt
│   └── mst_100000.txt
└── README.md

## Test Results

| Test Case        | Vertices | Kruskal Weight | Kruskal Time (ms) | Prim Weight | Prim Time (ms) |
|------------------|---------:|---------------:|------------------:|------------:|---------------:|
| `mst_10.txt`     | 10       |     94         |      0.0091       |     94      |     0.0132     |
| `mst_100.txt`    | 100      |     2080       |      0.0387       |     2080    |     0.1221     |
| `mst_10000.txt`  | 10,000   |    195396      |      5.6134       |     195396  |     28.6094    |
| `mst_50000.txt`  | 50,000   |      983827    |      24.414       |     983827  |     185.127    |
| `mst_100000.txt` | 100,000  |     1962047    |      48.116       |     1962047 |      398.157   |