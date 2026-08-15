#ifndef KRUSKAL_H
#define KRUSKAL_H

#include "../../assignment_01/src/csr.h"
#include "mst_types.h"

// Kruskal's algorithm on a CSR-represented weighted undirected graph.
// Edge extraction from CSR + sorting happens INSIDE this call, so it is
// included in the timed region, per assignment Section 8.
MSTResult kruskalMST(const CSRGraph& graph, int V);

#endif
