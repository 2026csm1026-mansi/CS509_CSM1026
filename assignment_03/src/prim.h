#ifndef PRIM_H
#define PRIM_H

#include "../../assignment_01/src/csr.h"
#include "mst_types.h"

// Prim's algorithm on a CSR-represented weighted undirected graph.
// Starts from startVertex (recommended: vertex 0, per assignment spec).
// Uses a min-priority-queue over CSR rows for the "cheapest edge to
// an outside vertex" step.
MSTResult primMST(const CSRGraph& graph, int V, int startVertex = 0);

#endif
