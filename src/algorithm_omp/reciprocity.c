#include "reciprocity.h"

void Graph_calculate_Reciprocity(Graph * graph, double ** reciprocity)
{
    Vertex_id vertex;
    unsigned int max_n_friends = 0; 
    
    // Config OpenMP
    omp_set_num_threads(omp_get_max_threads());
   
    for (vertex = 0; vertex < (*graph).n_vertexes; vertex++) {
        max_n_friends = MAX(MIN((*graph).vertexes[vertex].out_degree, (*graph).vertexes[vertex].in_degree), max_n_friends);
    }

    #pragma omp parallel
    {
        Vertex_id * friends;
        unsigned int n_friends;
        friends = (Vertex_id *) malloc(max_n_friends*sizeof(Vertex_id));
        #pragma omp for
        for (vertex = 0; vertex < (*graph).n_vertexes; vertex++) {
            Graph_vertex_friends(graph, vertex, &friends, &n_friends);
            if ((*graph).vertexes[vertex].out_degree > 0) {
                (*reciprocity)[vertex] = n_friends/((double) (*graph).vertexes[vertex].out_degree);
            }
            else {
                (*reciprocity)[vertex] = nan("");
            }
        }
        free(friends);
    }
}

