#include "reciprocity.h"

void Graph_calculate_Reciprocity(Graph * graph, double ** reciprocity)
{
    Vertex_id vertex;
    Vertex_id * friends;
    unsigned int n_friends, max_n_friends = 0; 
   
    // Calculate the maximum possible value for the friends list
    for (vertex = 0; vertex < (*graph).n_vertexes; vertex++) {
        max_n_friends = MAX(MIN((*graph).vertexes[vertex].out_degree, (*graph).vertexes[vertex].in_degree), max_n_friends);
    }
    
    // Create a vector for storing the friends list
    friends = (Vertex_id *) malloc(max_n_friends*sizeof(Vertex_id));

    // For each vertex, retrieve its friends list (reciprocal) and utilizes the size to calculate the reciprocity value
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

