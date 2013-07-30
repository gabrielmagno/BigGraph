#include "graph/graph.h"

#define ABS(a) (((a) > 0) ? (a) : (-(a)))

#define MAX_ITERATIONS 50
#define MAX_ERROR 1e-6
#define DAMPING_FACTOR 0.85

void Graph_calculate_PageRank(Graph * graph, double ** pagerank, int do_dangle_sum);

