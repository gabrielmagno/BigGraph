#include "pagerank.h"

void Graph_calculate_PageRank(Graph * graph, int do_dangle_sum, double ** pagerank)
{
    Vertex_id vertex;
    Vertex_id * predecessors;
    double * pagerank_new, * partial_values;
    double initial_value, damping_value, dangle_sum;
    unsigned int i, iteration, n_elegible, n_predecessors;
    
    pagerank_new = (double *) malloc((*graph).n_vertexes*sizeof(double));
    partial_values = (double *) malloc((*graph).n_vertexes*sizeof(double));

    // Pre-calculate values that will be used for all the vertexes
    initial_value = 1.0/(*graph).n_vertexes;
    damping_value = (1 - DAMPING_FACTOR)/((*graph).n_vertexes);
    n_elegible = (*graph).n_vertexes;

    // Initial values
    for (vertex = 0; vertex < (*graph).n_vertexes; vertex++) {
        (*pagerank)[vertex] = initial_value;
        pagerank_new[vertex] = 0.0;
    }
    
    // Iteration loop. Finishs if reaches the max number of iterations or 
    // the difference of the values between two iterations is minimal
    for (iteration = 1; (n_elegible > 0) && (iteration <= MAX_ITERATIONS); iteration++) {

        // Pre-calculate the partial values that each vertex will 'provide' to its successors
        for (vertex = 0; vertex < (*graph).n_vertexes; vertex++) {
            partial_values[vertex] = ((*pagerank)[vertex])/((*graph).vertexes[vertex].out_degree);
        }
        
        // Sum the partial values coming from the predecessors of each vertex
        for (vertex = 0; vertex < (*graph).n_vertexes; vertex++) {
           Graph_vertex_predecessors(graph, vertex, &predecessors, &n_predecessors);
           for (i = 0; i < n_predecessors; i++) {
               pagerank_new[vertex] += partial_values[predecessors[i]];
           }
        }

        // If required, realize the dangle sum, to guarantee that the sum of all pagerank values is equal to 1.0
        dangle_sum = 0.0;
        if (do_dangle_sum) {
            for (vertex = 0; vertex < (*graph).n_vertexes; vertex++) {
                if ((*graph).vertexes[vertex].out_degree == 0) {
                    dangle_sum += (*pagerank)[vertex];
                }
            }
            dangle_sum /= (*graph).n_vertexes;
        }

        // Update the values with the formula
        for (vertex = 0; vertex < (*graph).n_vertexes; vertex++) {
            pagerank_new[vertex] = damping_value + DAMPING_FACTOR*(pagerank_new[vertex] + dangle_sum);
        }
        
        // Calculate the delta between iterations to check if one more iterations is necessary
        n_elegible = 0;
        for (vertex = 0; vertex < (*graph).n_vertexes; vertex++) {
            if (ABS((*pagerank)[vertex] - pagerank_new[vertex]) > MAX_ERROR) {
                n_elegible++;
            }
            (*pagerank)[vertex] = pagerank_new[vertex];
            pagerank_new[vertex] = 0.0;
        }

    }

    free(pagerank_new);
    free(partial_values);
}

