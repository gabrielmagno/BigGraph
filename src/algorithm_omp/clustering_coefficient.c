#include "clustering_coefficient.h"

void Graph_calculate_ClusteringCoefficient(Graph * graph, double ** clustering_coefficient)
{
    Vertex_id vertex;
    unsigned int max_n_friends = 0;

    // Config OpenMP
    omp_set_num_threads(omp_get_max_threads());

    // Calculate the maximum possible value for the friends list
    for (vertex = 0; vertex < (*graph).n_vertexes; vertex++) {
        max_n_friends = MAX(MIN((*graph).vertexes[vertex].out_degree, (*graph).vertexes[vertex].in_degree), max_n_friends);
    }

    #pragma omp parallel
    {
        unsigned int i, j, n_friends, n_links, n_possible_links;
        Vertex_id * friends;

        // Create a vector for storing the friends list
        friends = (Vertex_id *) malloc(max_n_friends*sizeof(Vertex_id));

        // For each vertex
        #pragma omp for
        for (vertex = 0; vertex < (*graph).n_vertexes; vertex++) {

            // Retrieve the friends list to measure the maximum number of links possible among friends
            Graph_vertex_friends(graph, vertex, &friends, &n_friends);
            n_possible_links = n_friends*(n_friends-1);

            // Measure the actual number of links among friends to calculate the clustering coefficient
            n_links = 0;
            if (n_possible_links > 0) {
                for (i = 0; i < n_friends; i++) {
                    for (j = 0; j < n_friends; j++) {
                        if ((i != j) && Graph_edge_exists(graph, friends[i], friends[j])) {
                            n_links++;    
                        }
                    }
                }
                (*clustering_coefficient)[vertex] = n_links/((double) n_possible_links);
            }
            else {
                (*clustering_coefficient)[vertex] = nan("");
            }

        }

        free(friends);
    }
}

