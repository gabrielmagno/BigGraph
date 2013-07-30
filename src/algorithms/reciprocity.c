#include <stdio.h>
#include "graph.h"

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

void Graph_calculate_Reciprocity(Graph * graph, double ** reciprocity)
{
    Vertex_id vertex;
    Vertex_id * friends;
    unsigned int n_friends, max_n_friends; 
    clock_t time_start, time_end, ftime_start, ftime_end;
    
    fprintf(stderr, "* Calculating Reciprocity\n");
    ftime_start = clock();
    
    fprintf(stderr, "    - Calculate the maximum size necessary for the friends list... ");
    time_start = clock();
    max_n_friends = 0;
    for (vertex = 0; vertex < (*graph).n_vertexes; vertex++) {
        max_n_friends = MAX(MIN((*graph).vertexes[vertex].out_degree, (*graph).vertexes[vertex].in_degree), max_n_friends);
    }
    time_end = clock();
    fprintf(stderr, "OK [%lf s]\n", ((time_end - time_start)/((double) CLOCKS_PER_SEC)));

    fprintf(stderr, "    - Retrieve the friends list of each vertex... ");
    time_start = clock();
    friends = (Vertex_id *) malloc(max_n_friends*sizeof(Vertex_id));
    for (vertex = 0; vertex < (*graph).n_vertexes; vertex++) {
        Graph_vertex_friends(graph, vertex, &friends, &n_friends);
        (*reciprocity)[vertex] = n_friends/((double) (*graph).vertexes[vertex].out_degree);
    }
    free(friends);
    time_end = clock();
    fprintf(stderr, "OK [%lf s]\n", ((time_end - time_start)/((double) CLOCKS_PER_SEC)));

    ftime_end = clock();
    fprintf(stderr, "    + Total elapsed time: %lf s\n", ((ftime_end - ftime_start)/((double) CLOCKS_PER_SEC)));
}

int main(int argc, char * argv[])
{
    double * reciprocity;
    Graph graph;
    Vertex_id vertex;

    Graph_open(&graph, NULL);
    reciprocity = (double *) malloc(graph.n_vertexes*sizeof(double));

    Graph_calculate_Reciprocity(&graph, &reciprocity);

    for (vertex = 0; vertex < graph.n_vertexes; vertex++) {
        fprintf(stdout, "%d %f\n", vertex, reciprocity[vertex]);
    }
    
    Graph_close(&graph);
    free(reciprocity);

    return EXIT_SUCCESS;
}

