#include <stdio.h>
#include "graph.h"

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

void Graph_calculate_ClusteringCoefficient(Graph * graph, double ** clustering_coefficient)
{
    Vertex_id vertex;
    Vertex_id * friends;
    unsigned int i, j, max_n_friends = 0, n_friends, n_links, n_possible_links; 
    for (vertex = 0; vertex < (*graph).n_vertexes; vertex++) {
        max_n_friends = MAX(MIN((*graph).vertexes[vertex].out_degree, (*graph).vertexes[vertex].in_degree), max_n_friends);
    }
    friends = (Vertex_id *) malloc(max_n_friends*sizeof(Vertex_id));
    for (vertex = 0; vertex < (*graph).n_vertexes; vertex++) {
        Graph_vertex_friends(graph, vertex, &friends, &n_friends);
        n_possible_links = n_friends*(n_friends-1);
        n_links = 0;
        (*clustering_coefficient)[vertex] = 0.0;
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
    }
    free(friends);
}

int main(int argc, char * argv[])
{
    double * clustering_coefficient;
    Graph graph;
    Vertex_id vertex;

    Graph_open(&graph, NULL);
    clustering_coefficient = (double *) malloc(graph.n_vertexes*sizeof(double));

    Graph_calculate_ClusteringCoefficient(&graph, &clustering_coefficient);

    for (vertex = 0; vertex < graph.n_vertexes; vertex++) {
        fprintf(stdout, "%d %f\n", vertex, clustering_coefficient[vertex]);
    }
    
    Graph_close(&graph);
    free(clustering_coefficient);

    return EXIT_SUCCESS;
}

