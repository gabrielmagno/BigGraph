#include "reciprocity.h"

void Graph_calculate_Reciprocity(Graph * graph, double ** reciprocity)
{
    Vertex_id vertex;
    Vertex_id * friends;
    unsigned int n_friends, max_n_friends; 
    
    max_n_friends = 0;
    for (vertex = 0; vertex < (*graph).n_vertexes; vertex++) {
        max_n_friends = MAX(MIN((*graph).vertexes[vertex].out_degree, (*graph).vertexes[vertex].in_degree), max_n_friends);
    }
    friends = (Vertex_id *) malloc(max_n_friends*sizeof(Vertex_id));

    for (vertex = 0; vertex < (*graph).n_vertexes; vertex++) {
        Graph_vertex_friends(graph, vertex, &friends, &n_friends);
        (*reciprocity)[vertex] = n_friends/((double) (*graph).vertexes[vertex].out_degree);
    }

    free(friends);
}

