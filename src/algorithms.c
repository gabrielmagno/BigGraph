#include <stdio.h>
#include <time.h>

#include "graph/graph.h"

#include "algorithm/reciprocity.h"
#include "algorithm/clustering_coefficient.h"
#include "algorithm/pagerank.h"
#include "algorithm/weakly_connected_components.h"
#include "algorithm/strongly_connected_components.h"

void clock_start(char * message, clock_t * time_start, clock_t * time_stop) 
{
    fprintf(stderr, "+ %s... ", message);
    *time_start = clock();
}

void clock_stop(clock_t * time_start, clock_t * time_stop) 
{
    *time_stop = clock();
    fprintf(stderr, "OK [%lf s]\n", (((*time_stop) - (*time_start))/((double) CLOCKS_PER_SEC)));
}

int main(int argc, char * argv[])
{
    Graph graph;
    Vertex_id vertex;
    
    double * reciprocity;
    double * clustering_coefficient;
    double * pagerank;
    unsigned int * weakly_connected_components;
    unsigned int * strongly_connected_components;

    FILE * outfile;
    clock_t time_start, time_stop;

    clock_start("Reading graph", &time_start, &time_stop);
    Graph_open(&graph, argv[1]);
    clock_stop(&time_start, &time_stop);

    clock_start("Allocating structures", &time_start, &time_stop);
    reciprocity = (double *) malloc(graph.n_vertexes*sizeof(double));
    clustering_coefficient = (double *) malloc(graph.n_vertexes*sizeof(double));
    pagerank = (double *) malloc(graph.n_vertexes*sizeof(double));
    weakly_connected_components = (unsigned int *) malloc(graph.n_vertexes*sizeof(unsigned int));
    strongly_connected_components = (unsigned int *) malloc(graph.n_vertexes*sizeof(unsigned int));
    clock_stop(&time_start, &time_stop);

    clock_start("Calculating Reciprocity", &time_start, &time_stop);
    Graph_calculate_Reciprocity(&graph, &reciprocity);
    clock_stop(&time_start, &time_stop);

    clock_start("Calculating Clustering Coef", &time_start, &time_stop);
    Graph_calculate_ClusteringCoefficient(&graph, &clustering_coefficient);
    clock_stop(&time_start, &time_stop);

    clock_start("Calculating PageRank", &time_start, &time_stop);
    Graph_calculate_PageRank(&graph, &pagerank, 1);
    clock_stop(&time_start, &time_stop);

    clock_start("Calculating Weakly CC", &time_start, &time_stop);
    Graph_calculate_WeaklyConnectedComponents(&graph, &weakly_connected_components);
    clock_stop(&time_start, &time_stop);

    clock_start("Calculating Strongly CC", &time_start, &time_stop);
    Graph_calculate_StronglyConnectedComponents(&graph, &strongly_connected_components);
    clock_stop(&time_start, &time_stop);
   
    clock_start("Writing results", &time_start, &time_stop);
    outfile = fopen(argv[2], "w");
    for (vertex = 0; vertex < graph.n_vertexes; vertex++) {
        fprintf(outfile, "%d %d %d %.12lf %.12lf %.12lf %d %d\n", vertex, graph.vertexes[vertex].in_degree,
                                                             graph.vertexes[vertex].out_degree,
                                                             reciprocity[vertex],
                                                             clustering_coefficient[vertex],
                                                             pagerank[vertex],
                                                             weakly_connected_components[vertex],
                                                             strongly_connected_components[vertex]);
    }
    fclose(outfile);
    clock_stop(&time_start, &time_stop);
   
    clock_start("Deallocating graph", &time_start, &time_stop);
    Graph_close(&graph);
    clock_stop(&time_start, &time_stop);
    
    clock_start("Deallocating structures", &time_start, &time_stop);
    free(reciprocity);
    free(clustering_coefficient);
    free(pagerank);
    free(weakly_connected_components);
    free(strongly_connected_components);
    clock_stop(&time_start, &time_stop);

    return EXIT_SUCCESS;
}

