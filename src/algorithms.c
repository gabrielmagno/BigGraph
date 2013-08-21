#include <stdio.h>
#include <sys/time.h>

#include "graph/graph.h"

#include "algorithm/reciprocity.h"
#include "algorithm/clustering_coefficient.h"
#include "algorithm/pagerank.h"
#include "algorithm/weakly_connected_components.h"
#include "algorithm/strongly_connected_components.h"

typedef struct time_measure {
    struct timeval start;
    struct timeval stop;
    float total;
} time_measure;

void time_start(char * message, time_measure * time) 
{
    fprintf(stderr, "+ %s... ", message);
    gettimeofday(&((*time).start), NULL);
}

void time_stop(time_measure * time) 
{
    gettimeofday(&((*time).stop), NULL);
    (*time).total = ((((*time).stop.tv_sec - (*time).start.tv_sec)*1000000) + ((*time).stop.tv_usec - (*time).start.tv_usec))/1000000;
    fprintf(stderr, "OK [%.2f s]\n", (*time).total);
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

    FILE * infile, * outfile;
    time_measure time;

    time_start("Reading graph", &time);
    if (argc >= 2) {
        infile = fopen(argv[1], "r");
    }
    else {
        infile = stdin;
    }
    Graph_open(&graph, infile);
    if (argc >= 2) {
        fclose(infile);
    }
    time_stop(&time);

    time_start("Allocating structures", &time);
    reciprocity = (double *) malloc(graph.n_vertexes*sizeof(double));
    clustering_coefficient = (double *) malloc(graph.n_vertexes*sizeof(double));
    pagerank = (double *) malloc(graph.n_vertexes*sizeof(double));
    weakly_connected_components = (unsigned int *) malloc(graph.n_vertexes*sizeof(unsigned int));
    strongly_connected_components = (unsigned int *) malloc(graph.n_vertexes*sizeof(unsigned int));
    time_stop(&time);

    time_start("Calculating Reciprocity", &time);
    Graph_calculate_Reciprocity(&graph, &reciprocity);
    time_stop(&time);

    time_start("Calculating Clustering Coef", &time);
    Graph_calculate_ClusteringCoefficient(&graph, &clustering_coefficient);
    time_stop(&time);

    time_start("Calculating PageRank", &time);
    Graph_calculate_PageRank(&graph, &pagerank, 1);
    time_stop(&time);

    time_start("Calculating Weakly CC", &time);
    Graph_calculate_WeaklyConnectedComponents(&graph, &weakly_connected_components);
    time_stop(&time);

    time_start("Calculating Strongly CC", &time);
    Graph_calculate_StronglyConnectedComponents(&graph, &strongly_connected_components);
    time_stop(&time);
   
    time_start("Writing results", &time);
    if (argc >= 3) {
        outfile = fopen(argv[2], "w");
    }
    else {
        outfile = stdout;
    }
    for (vertex = 0; vertex < graph.n_vertexes; vertex++) {
        fprintf(outfile, "%d %d %d %.12lf %.12lf %.12lf %d %d\n", vertex, graph.vertexes[vertex].in_degree,
                                                             graph.vertexes[vertex].out_degree,
                                                             reciprocity[vertex],
                                                             clustering_coefficient[vertex],
                                                             pagerank[vertex],
                                                             weakly_connected_components[vertex],
                                                             strongly_connected_components[vertex]);
    }
    if (argc >= 3) {
        fclose(outfile);
    }
    time_stop(&time);
   
    time_start("Deallocating graph", &time);
    Graph_close(&graph);
    time_stop(&time);
    
    time_start("Deallocating structures", &time);
    free(reciprocity);
    free(clustering_coefficient);
    free(pagerank);
    free(weakly_connected_components);
    free(strongly_connected_components);
    time_stop(&time);

    return EXIT_SUCCESS;
}

