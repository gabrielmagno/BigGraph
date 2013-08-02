#include <math.h>
#include <omp.h>
#include "graph/graph.h"

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

void Graph_calculate_ClusteringCoefficient(Graph * graph, double ** clustering_coefficient);

